// Fill out your copyright notice in the Description page of Project Settings.

#include "Source/TowerActor.h"
#include "TowerSpawnPlaceholder.h"
#include "TowerBuildingScaffolding.h"
#include "Components/WidgetComponent.h"
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
		InteractEmptyWidgetHolder = FindComponentByClass<UWidgetComponent>();
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
		
		//Force disable interaction widget
		ToggleWidget(InteractEmptyWidgetHolder, false);

		//Force disable further iteration until next BeginOverlap event
		UpdateInteractionState(false);
	}
}

void ATowerSpawnPlaceholder::TowerBuildingFinishedHandler(ATowerActor* tower)
{
	SpawnedScaffolding = nullptr;
	SpawnedTower = tower;
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
	return SpawnedTower != nullptr;
}

#pragma endregion

#pragma endregion 

#pragma region Interation

void ATowerSpawnPlaceholder::InitializeInteractions()
{
    try
    {
		UpdateInteractionState(false);

    	//Get all static mesh components
    	TArray<UStaticMeshComponent*> meshComponents;
    	GetComponents<UStaticMeshComponent>(meshComponents);

    	//Grab first one and treat as a graphics mesh
    	if (meshComponents.Num() > 0)
    		PlaceholderMeshComponent = meshComponents[0];

    	//Get all static mesh components
    	//TArray<UParticleSystemComponent*> particleComponents;
    	//GetComponents<UParticleSystemComponent>(particleComponents);

    	//GeneralPurposeUtils::DisplayScreenMessage(FString::FromInt(particleComponents.Num()));
    }
    catch (...)
    {
    	GeneralPurposeUtils::DisplayScreenMessage("Could not get placeholder mesh", FColor::Red);
    }
}

void ATowerSpawnPlaceholder::UpdateInteractionState(bool isInteractionAllowed)
{
	isInInteractionRange = isInteractionAllowed;
	
	//Enable/Disable Build Widget only if no tower built yet
	if (IsEmpty())
	{
		ToggleWidget(InteractEmptyWidgetHolder, isInteractionAllowed);
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

#pragma endregion

#pragma region TEMP

void ATowerSpawnPlaceholder::TempInputProcess()
{
	if (!isInInteractionRange)
		return;

	if (CanSpawnTower())
		BuildTower(TempTowerToPlace);
}

#pragma endregion

