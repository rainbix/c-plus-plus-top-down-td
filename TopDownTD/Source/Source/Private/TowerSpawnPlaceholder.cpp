// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawnPlaceholder.h"
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
	
	InitializeWidgets();
	InitializeInteractions();
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
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FVector spawnPos = GetActorLocation();
		FRotator spawnRot(0, 0, 0);

		spawnedTower = GetWorld()->SpawnActor<ATowerActor>(towerToSpawn, spawnPos, spawnRot);
		
		if (spawnedTower)
		{
			//Disable Placeholder mesh 
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
	return isInInteractionRange && !spawnedTower;
}

#pragma endregion 

#pragma region Interation

void ATowerSpawnPlaceholder::InitializeInteractions()
{
	UpdateInteractionState(false);
    	
    try
    {
    	TArray<UStaticMeshComponent*> Components;
    	GetComponents<UStaticMeshComponent>(Components);

    	placeholderMeshComponent = Components[0];
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
	if (!spawnedTower)
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

