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
	GENERATED_BODY()	
	
	//TODO: Add delegate when Tower has finished building and return pointer to the tower
	
public:	
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
