// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBuildingScaffolding.generated.h"

class ATowerActor;
class UProgressBarWidget;
class SimpleInterpolator;

UCLASS()
class SOURCE_API ATowerBuildingScaffolding : public AActor
{
	//Purpose of the class is to be a graphics placeholder while Tower build time is ticking.
	//After build time elapsed placeholder is going to be replaced by a tower instance
	
	GENERATED_BODY()	

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingFinished, ATowerActor*)
	FOnBuildingFinished OnBuildingFinishedDelegate;
	
	ATowerBuildingScaffolding();

	virtual void Tick(float DeltaTime) override;
	void InitializeActor(const TSubclassOf<ATowerActor> towerToSpawn, int buildTime);
	
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY()
	TSubclassOf<ATowerActor> TowerToSpawnClass;
	
	UPROPERTY()
	UProgressBarWidget* TimerBarWidget;

	TUniquePtr<SimpleInterpolator> BuildTimeInterpolator = nullptr;

	void ProcessBuilding(float deltaTime);
	void SpawnTower(const TSubclassOf<ATowerActor> towerToSpawn);
	
	bool TryGetTimerBarWidget();
};
