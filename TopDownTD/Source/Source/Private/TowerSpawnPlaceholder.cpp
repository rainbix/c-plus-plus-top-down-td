// Fill out your copyright notice in the Description page of Project Settings.

#include "Source/TowerActor.h"
#include "TowerSpawnPlaceholder.h"
#include "TowerBuildingScaffolding.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Source/HUD/GameplayHUD.h"
#include "Source/Tools/GeneralPurposeUtils.h"

#pragma region Overrides

ATowerSpawnPlaceholder::ATowerSpawnPlaceholder()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerSpawnPlaceholder::BeginPlay()
{
	Super::BeginPlay();

	try
	{
		InitializeWidgets();
		InitializeInteractions();

		//Get reference to HUD class
		const APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		hud = Cast<AGameplayHUD>(playerController->GetHUD());
		if (hud)
		{
			//hud->OnTowerBuildRequest.AddUObject(this, &ATowerSpawnPlaceholder::TowerBuildRequestHandler);
		}
	}
	catch (...)
	{
		GeneralPurposeUtils::DisplayScreenMessage("BeginPlay failed", FColor::Red);
	}
}

void ATowerSpawnPlaceholder::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	UpdateInteractionState(true);
}

void ATowerSpawnPlaceholder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	UpdateInteractionState(false);
}

#pragma endregion

#pragma region Widgets

void ATowerSpawnPlaceholder::InitializeWidgets()
{
	try
	{
		InteractEmptyWidgetHolder = InitializeFromComponent<UWidgetComponent>(0);
	}
	catch (...)
	{
		GeneralPurposeUtils::DisplayScreenMessage("Could not get UWidgetComponent", FColor::Red);
	}
}

void ATowerSpawnPlaceholder::ToggleWidget(UWidgetComponent* widget, bool isActive)
{
	if (widget)
		widget->SetVisibility(isActive);
}

#pragma endregion 

#pragma region Towers

void ATowerSpawnPlaceholder::TowerBuildRequestHandler(TSubclassOf<ATowerActor> selectedTowerClass)
{
	hud->OnTowerBuildRequest.Remove(towerBuildRequestDelegateHandle);
	
	if (selectedTowerClass)
		BuildTower(selectedTowerClass);
}

void ATowerSpawnPlaceholder::BuildTower(const TSubclassOf<ATowerActor> towerToBuild)
{
	if (!towerToBuild)
	{
		GeneralPurposeUtils::DisplayScreenMessage("[TowerSpawnPlaceholder] Nothing to spawn", FColor::Red);
		return;
	}
	
	//Prepare spawn
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	const FVector spawnPos = GetActorLocation();
	const FRotator spawnRot(0, 0, 0);

	//Spawn scaffolding first. When building timer will be finished corresponding tower is placed
	SpawnedScaffolding = GetWorld()->SpawnActor<ATowerBuildingScaffolding>(ScaffoldingActorClass, spawnPos, spawnRot);
	
	if (SpawnedScaffolding)
	{
		//Initialize scaffolding
		SpawnedScaffolding->OnBuildingFinishedDelegate.AddUObject(this, &ATowerSpawnPlaceholder::TowerBuildingFinishedHandler);
		SpawnedScaffolding->InitializeActor(towerToBuild, BuildTime);
		
		//Disable Placeholder mesh
		if (PlaceholderMeshComponent)
			PlaceholderMeshComponent->SetVisibility(false);
		
		//Force disable interaction widget and build ready effect
		ToggleWidget(InteractEmptyWidgetHolder, false);
		ToggleEffect(BuildReadyEffectComponent, false);

		//Force disable further iteration until next BeginOverlap event
		UpdateInteractionState(false);
	}
}

void ATowerSpawnPlaceholder::TowerBuildingFinishedHandler(ATowerActor* tower)
{	
	SpawnedScaffolding = nullptr;
	spawnedTower = tower;
}

#pragma region Tower State Properties

bool ATowerSpawnPlaceholder::CanSpawnTower() const
{
	return isInInteractionRange && IsEmpty();
}

bool ATowerSpawnPlaceholder::IsEmpty() const
{
	return !IsTowerBuilding() && !IsTowerReady();
}

bool ATowerSpawnPlaceholder::IsTowerBuilding() const
{
	return SpawnedScaffolding != nullptr;
}

bool ATowerSpawnPlaceholder::IsTowerReady() const
{
	return spawnedTower != nullptr;
}

#pragma endregion

#pragma endregion 

#pragma region Interation

void ATowerSpawnPlaceholder::InitializeInteractions()
{
    try
    {
    	//Grab first static mesh and treat as a graphics mesh
    	PlaceholderMeshComponent = InitializeFromComponent<UStaticMeshComponent>(0);
    	
    	//Grab first particle system and treat as a interaction effect
    	BuildReadyEffectComponent = InitializeFromComponent<UParticleSystemComponent>(0);

    	//Set initial state as not interacting with anything
    	UpdateInteractionState(false);
    }
    catch (...)
    {
    	GeneralPurposeUtils::DisplayScreenMessage("Could not get placeholder mesh", FColor::Red);
    }
}

template <typename T>
T* ATowerSpawnPlaceholder::InitializeFromComponent(int indexToTake)
{
	//Get all components
	TArray<T*> components;
	GetComponents<T>(components);

	//Fill object with specified index from received components list
	if (components.Num() > indexToTake)
		return components[indexToTake];

	return nullptr;
}

void ATowerSpawnPlaceholder::UpdateInteractionState(bool isInteractionAllowed)
{
	isInInteractionRange = isInteractionAllowed;
	
	//Enable/Disable Build Widget only if no tower built yet
	if (IsEmpty())
	{
		ToggleWidget(InteractEmptyWidgetHolder, isInInteractionRange);
		ToggleEffect(BuildReadyEffectComponent, isInInteractionRange);
	}
	else if (isInInteractionRange && IsTowerBuilding())
	{
		//Do some stuff if tower is building (speed up for coins, etc)
	}
	else if (isInInteractionRange && IsTowerReady())
	{
		//Do some stuff if tower is build and ready (upgrade, destroy, etc)
	}
}

void ATowerSpawnPlaceholder::ProcessInputRequest()
{
	if (!isInInteractionRange)
		return;

	if (CanSpawnTower())
	{
		if (hud)
		{
			hud->OnTowerBuildRequest.Remove(towerBuildRequestDelegateHandle);
			towerBuildRequestDelegateHandle = hud->OnTowerBuildRequest.AddUObject(this, &ATowerSpawnPlaceholder::TowerBuildRequestHandler);
			
			hud->ShowTowerShopWidget();	
		}
		else
		{
			GeneralPurposeUtils::DisplayScreenMessage("No reference to HUD", FColor::Red);
		}
	}
	else
		GeneralPurposeUtils::DisplayScreenMessage("Can't place tower", FColor::Red);
}

bool ATowerSpawnPlaceholder::IsInInteractionRange() const
{
	return  isInInteractionRange;
}

#pragma endregion

#pragma region Effects

void ATowerSpawnPlaceholder::ToggleEffect(UParticleSystemComponent* effectComponent, bool isActive)
{
	if (effectComponent)
		effectComponent->SetActive(isActive);
}

#pragma endregion


