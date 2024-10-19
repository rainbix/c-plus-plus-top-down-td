// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawnPlaceholder.generated.h"

class ATowerActor;
class UWidgetComponent;
class ATowerBuildingScaffolding;
class UParticleSystemComponent;

//TODO: Expose current state as enum
enum class ETowerStates : uint8
{
	State1, State2, State3
};

UCLASS()
class SOURCE_API ATowerSpawnPlaceholder : public AActor
{
	//Purpose of the class is to be a Spawn Point for the Tower
	
	GENERATED_BODY()

public:	
	ATowerSpawnPlaceholder();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	bool IsInInteractionRange() const;
	bool CanSpawnTower() const;
	void BuildTower(const TSubclassOf<ATowerActor> towerToSpawn, float buildTime);

protected:
	virtual void BeginPlay() override;

private:

	#pragma region Towers
	
	UPROPERTY()
	ATowerActor* spawnedTower;
	
	void TowerBuildingFinishedHandler(ATowerActor* tower);

	#pragma region Tower State Properties
	
	bool IsEmpty() const;
	bool IsTowerBuilding() const;
	bool IsTowerReady() const;

	#pragma endregion
	
	#pragma endregion

	#pragma region Scaffolding

	UPROPERTY(EditDefaultsOnly, Category="References")
	TSubclassOf<ATowerBuildingScaffolding> ScaffoldingActorClass;
	
	UPROPERTY()
	ATowerBuildingScaffolding* spawnedScaffolding;

	#pragma endregion
	
	#pragma region Interation

	bool isInInteractionRange;

	UPROPERTY()
	UStaticMeshComponent* PlaceholderMeshComponent;
	
	void InitializeInteractions();
	void UpdateInteractionState(bool isInteractionAllowed);

	template <typename T>
	T* InitializeFromComponent(int indexToTake);

	#pragma endregion

	#pragma region Effects

	UPROPERTY()
	UParticleSystemComponent* BuildReadyEffectComponent;

	static void ToggleEffect(UParticleSystemComponent* effectComponent, bool isActive);
	
	#pragma endregion 
	
	#pragma region Widgets
	
	UPROPERTY()
	UWidgetComponent* InteractEmptyWidgetHolder;

	void InitializeWidgets();
	static void ToggleWidget(UWidgetComponent* widget, bool isActive);
	
	#pragma endregion
};
