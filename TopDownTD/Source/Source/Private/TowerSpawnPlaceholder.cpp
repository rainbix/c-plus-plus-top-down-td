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

void ATowerSpawnPlaceholder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO: Building progress bar should be implemented here
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

void ATowerSpawnPlaceholder::SpawnTower(const TSubclassOf<ATowerActor> towerToSpawn)
{
	if (towerToSpawn)
	{
		//Prepare spawn
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		const FVector spawnPos = GetActorLocation();
		const FRotator spawnRot(0, 0, 0);

		//Spawn scaffolding first. When building timer will be finished corresponding tower is placed
		spawnedScaffolding = GetWorld()->SpawnActor<ATowerBuildingScaffolding>(scaffoldingActorClass, spawnPos, spawnRot);
		
		if (spawnedScaffolding)
		{
			//Initialize scaffolding
			spawnedScaffolding->InitializeActor(towerToSpawn, BuildTime);

			//TODO: Subscribe on scaffoldings build finish event
			
			//Disable Placeholder mesh
			if (placeholderMeshComponent)
				placeholderMeshComponent->SetVisibility(false);
			
			//Force disable interaction widget
			ToggleWidget(InteractEmptyWidgetHolder, false);

			//Force disable further iteration until next BeginOverlap event
			UpdateInteractionState(false);
		}
	}
	else
	{
		GeneralPurposeUtils::DisplayScreenMessage("Nothing to spawn", FColor::Red);
	}
}

bool ATowerSpawnPlaceholder::CanSpawnTower() const
{
	return isInInteractionRange && IsEmpty();
}

bool ATowerSpawnPlaceholder::IsEmpty() const
{
	return !spawnedScaffolding && !spawnedTower;
}

#pragma endregion 

#pragma region Interation

void ATowerSpawnPlaceholder::InitializeInteractions()
{
    try
    {
		UpdateInteractionState(false);
    	
    	//TArray<UStaticMeshComponent*> Components;
    	//GetComponents<UStaticMeshComponent>(Components);

    	//placeholderMeshComponent = Components[0];
    }
    catch (...)
    {
    	GeneralPurposeUtils::DisplayScreenMessage("Could not get placeholder mesh", FColor::Red);
    }
}

void ATowerSpawnPlaceholder::UpdateInteractionState(bool isInteractionAllowed)
{
	isInInteractionRange = isInteractionAllowed;
	
	//Enable Build widget only if no tower built yet
	if (IsEmpty())
		ToggleWidget(InteractEmptyWidgetHolder, isInteractionAllowed);
}

#pragma endregion

#pragma region TEMP

void ATowerSpawnPlaceholder::TempInputProcess()
{
	if (!isInInteractionRange)
		return;

	if (CanSpawnTower())
		SpawnTower(TempTowerToPlace);
}

#pragma endregion

