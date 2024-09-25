// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBuildingScaffolding.h"
#include "Source/TowerActor.h"
#include "Components/WidgetComponent.h"
#include "Source/HUD/ProgressBarWidget.h"
#include "Source/Tools/GeneralPurposeUtils.h"

#pragma region Overrides

ATowerBuildingScaffolding::ATowerBuildingScaffolding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerBuildingScaffolding::BeginPlay()
{
	Super::BeginPlay();

	if (TryGetTimerBarWidget())
		TimerBarWidget->InitializeWidget(100, 0);

	BuildTimeInterpolator = MakeUnique<SimpleInterpolator>(1);
}

void ATowerBuildingScaffolding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessBuilding(DeltaTime);
}

#pragma endregion

void ATowerBuildingScaffolding::InitializeActor(const TSubclassOf<ATowerActor> targetTowerClass, int buildTime)
{
	TowerToSpawnClass = targetTowerClass;

	BuildTimeInterpolator->ResetWithNewTime(buildTime);
	BuildTimeInterpolator->Start();
}

void ATowerBuildingScaffolding::ProcessBuilding(float deltaTime)
{
	if (!BuildTimeInterpolator || !BuildTimeInterpolator->IsActive())
		return;

	//Process interpolator
	BuildTimeInterpolator->ProcessTick(deltaTime);

	//Cast intepolator's state into progress bar value
	const int progressPercent = BuildTimeInterpolator->Progress() * 100;
	TimerBarWidget->SetValue(progressPercent);

	//Finish interpolation
	if (BuildTimeInterpolator->IsElapsed())
	{
		BuildTimeInterpolator->Stop();

		SpawnTower(TowerToSpawnClass);
		Destroy();
	}
}

void ATowerBuildingScaffolding::SpawnTower(const TSubclassOf<ATowerActor> targetTowerClass)
{
	if (!targetTowerClass)
	{
		GeneralPurposeUtils::DisplayScreenMessage("Nothing to spawn", FColor::Red);
		return;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	FVector spawnPos = GetActorLocation();
	FRotator spawnRot(0, 0, 0);

	if (const auto spawnedTower = GetWorld()->SpawnActor<ATowerActor>(targetTowerClass, spawnPos, spawnRot))
	{
		//TODO: Broadcast event
		GeneralPurposeUtils::DisplayScreenMessage("Tower spawned " + spawnedTower->GetName());
	}
}


bool ATowerBuildingScaffolding::TryGetTimerBarWidget()
{
	try
	{
		if (const auto widgetComponent = FindComponentByClass<UWidgetComponent>())
		{
			if (const auto owningWidget = widgetComponent->GetWidget())
			{
				TimerBarWidget = Cast<UProgressBarWidget>(owningWidget);
				return true;
			}
		}
	}
	catch (...)
	{
		GeneralPurposeUtils::DisplayScreenMessage("FAIL");
	}


	return false;
}
