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


void UTowerBuildController::TowerBuildRequestHandler(TSubclassOf<ATowerActor> selectedTowerClass)
{
	if (selectedTowerClass && activePlaceholder)
	{
		activePlaceholder->BuildTower(selectedTowerClass, BuildTime);
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

		//Find first placeholder that can spawn a tower
		if (towerPlaceholder->CanSpawnTower())
		{
			//Save selected placeholder as active
			activePlaceholder = towerPlaceholder;

			//Show Tower Shop UI
			if (hud)
				hud->ShowTowerShopWidget();
			
			break;
		}
		//else ... Add here other possible interactions (eg upgrade tower, destroy tower)
	}
}
