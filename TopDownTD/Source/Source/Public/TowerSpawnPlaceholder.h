// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawnPlaceholder.generated.h"

class ATowerActor;
class AGameplayHUD;
class UWidgetComponent;
class ATowerBuildingScaffolding;
class UParticleSystemComponent;

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
	void ProcessInputRequest();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AGameplayHUD* hud;
	
	#pragma region Towers

	FDelegateHandle towerBuildRequestDelegateHandle;
	
	UPROPERTY()
	ATowerActor* spawnedTower;
	
	void TowerBuildRequestHandler(TSubclassOf<ATowerActor> selectedTowerClass);
	void BuildTower(const TSubclassOf<ATowerActor> towerToSpawn);
	void TowerBuildingFinishedHandler(ATowerActor* tower);

	#pragma region Tower State Properties
	
	bool CanSpawnTower() const;
	bool IsEmpty() const;
	bool IsTowerBuilding() const;
	bool IsTowerReady() const;

	#pragma endregion
	
	#pragma endregion

	#pragma region Scaffolding

	UPROPERTY(EditDefaultsOnly, Category="References")
	TSubclassOf<ATowerBuildingScaffolding> ScaffoldingActorClass;
	
	UPROPERTY()
	ATowerBuildingScaffolding* SpawnedScaffolding;

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

	#pragma region TEMP

	//TODO: TO be replaced by PlayerController input when Anton finishes his refactor
	
	
	//TODO: TO be replaced by config file params
	UPROPERTY(EditDefaultsOnly, Category="Temp")
	int BuildTime;
	
	#pragma endregion 
};
