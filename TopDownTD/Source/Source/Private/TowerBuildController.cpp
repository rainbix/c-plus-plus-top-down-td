// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBuildController.h"
#include "MyPlayerController.h"
#include "TowerSpawnPlaceholder.h"
#include "Source/HUD/GameplayHUD.h"
#include "Source/TowerActor.h"
#include "Source/Tools/GeneralPurposeUtils.h"

void UTowerBuildController::BeginPlay()
{
	Super::BeginPlay();
	
	//It is expected component's owner is a Player Controller itself.
	//In case of changing the owner replace with playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (const auto playerController = Cast<AMyPlayerController>(GetOwner()))
	{
		//Hook to input event
		playerController->OnBuildInputDelegate.AddUObject(this, &UTowerBuildController::BuildInputHandler);

		//Get HUD and hook to tower build event
		hud = Cast<AGameplayHUD>(playerController->GetHUD());
		if (hud)
		{
			hud->OnTowerBuildRequest.AddUObject(this, &UTowerBuildController::TowerBuildRequestHandler);
		}
	}

	world = GetWorld();
}

void UTowerBuildController::RegisterPlaceholder(ATowerSpawnPlaceholder* towerPlaceholder)
{
	if (towerPlaceholder)
		TowerSpawnPlaceholders.AddUnique(towerPlaceholder);
}

void UTowerBuildController::BuildInputHandler()
{
	TryShowTowerShop();
}


void UTowerBuildController::TowerBuildRequestHandler(TSubclassOf<ATowerActor> selectedTowerClass, int buildTime)
{
	if (selectedTowerClass && activePlaceholder)
	{
		activePlaceholder->BuildTower(selectedTowerClass, buildTime);
		activePlaceholder = nullptr;
	}
	else
	{
		GeneralPurposeUtils::DisplayScreenMessage("[UTowerBuildController] [TowerBuildRequestHandler] Nothing to build", FColor::Red);
	}
}


void UTowerBuildController::TryShowTowerShop()
{
	for (const auto towerPlaceholder : TowerSpawnPlaceholders)
	{
		if (!towerPlaceholder || !towerPlaceholder->IsInInteractionRange())
			continue;

		const ETowerStates towerState = towerPlaceholder->GetTowerState();
		
		//Find first empty placeholder to spawn a tower
		if (towerState == ETowerStates::IsEmpty)
		{
			//Save selected placeholder as active
			activePlaceholder = towerPlaceholder;

			//Show Tower Shop UI
			if (hud)
				hud->ShowTowerShopWidget();
			
			break;
		}

		if (towerState == ETowerStates::IsTowerBuilding)
		{
			//... Add here other possible interactions (speed up, cancel)
			break;
		}

		if (towerState == ETowerStates::IsTowerReady)
		{
			//... Add here other possible interactions (upgrade, destroy tower)
			break;
		}
	}
}
