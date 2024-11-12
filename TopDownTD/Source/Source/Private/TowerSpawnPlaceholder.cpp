// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerSpawnPlaceholder.h"
#include "PlayerCharacterSource.h"
#include "TowerBuildController.h"
#include "Source/TowerActor.h"
#include "TowerBuildingScaffolding.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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

		//Register itself in TowerBuildController
		if (const APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (UTowerBuildController* towerBuildController = playerController->FindComponentByClass<UTowerBuildController>())
			{
				towerBuildController->RegisterPlaceholder(this);
			}
		}
	}
	catch (...)
	{
		GeneralPurposeUtils::DisplayScreenMessage("[ATowerSpawnPlaceholder] BeginPlay failed", FColor::Red);
	}
}

void ATowerSpawnPlaceholder::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//Update interaction only if collides with a player
	if (Cast<APlayerCharacterSource>(OtherActor))
		UpdateInteractionState(true);
}

void ATowerSpawnPlaceholder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	//Update interaction only if collides with a player
	if (Cast<APlayerCharacterSource>(OtherActor))
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

void ATowerSpawnPlaceholder::BuildTower(const TSubclassOf<ATowerActor> towerToBuild, int buildTime)
{
	if (!towerToBuild)
	{
		GeneralPurposeUtils::DisplayScreenMessage("[TowerSpawnPlaceholder] Nothing to spawn", FColor::Red);
		return;
	}

	//Clamp min build time to 1 sec
	buildTime = FMath::Clamp(buildTime, 1, buildTime);
	
	//Prepare spawn
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	const FVector spawnPos = GetActorLocation();
	const FRotator spawnRot(0, 0, 0);

	//Spawn scaffolding first. When building timer will be finished corresponding tower is placed
	spawnedScaffolding = GetWorld()->SpawnActor<ATowerBuildingScaffolding>(ScaffoldingActorClass, spawnPos, spawnRot);
	
	if (spawnedScaffolding)
	{
		//Initialize scaffolding
		spawnedScaffolding->OnBuildingFinishedDelegate.AddUObject(this, &ATowerSpawnPlaceholder::TowerBuildingFinishedHandler);
		spawnedScaffolding->InitializeActor(towerToBuild, buildTime);
		
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
	spawnedScaffolding = nullptr;
	spawnedTower = tower;
}

ETowerStates ATowerSpawnPlaceholder::GetTowerState() const
{
	//Is Ready
	if (spawnedTower != nullptr)
		return ETowerStates::IsTowerReady;

	//Is Building
	if (spawnedScaffolding != nullptr)
		return ETowerStates::IsTowerBuilding;

	//Is Empty
	return ETowerStates::IsEmpty;
}

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

	const ETowerStates state = GetTowerState();
	
	//Enable/Disable Build Widget only if no tower built yet
	if (state == ETowerStates::IsEmpty)
	{
		ToggleWidget(InteractEmptyWidgetHolder, isInInteractionRange);
		ToggleEffect(BuildReadyEffectComponent, !isInInteractionRange);
	}
	else if (state == ETowerStates::IsTowerBuilding)
	{
		//if (isInInteractionRange)
		//Do some stuff if tower is building (speed up for coins, etc)
	}
	else if (state == ETowerStates::IsTowerReady)
	{
		//if (isInInteractionRange)
		//Do some stuff if tower is build and ready (upgrade, destroy, etc)
	}
}

bool ATowerSpawnPlaceholder::IsInInteractionRange() const
{
	return isInInteractionRange;
}

#pragma endregion

#pragma region Effects

void ATowerSpawnPlaceholder::ToggleEffect(UParticleSystemComponent* effectComponent, bool isActive)
{
	if (effectComponent)
		effectComponent->SetActive(isActive);
}

#pragma endregion


