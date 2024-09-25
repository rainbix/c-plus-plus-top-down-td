// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawnPlaceholder.generated.h"

class ATowerActor;
class UWidgetComponent;
class ATowerBuildingScaffolding;

UCLASS()
class SOURCE_API ATowerSpawnPlaceholder : public AActor
{
	GENERATED_BODY()

	//TODO: FIx placeholder mex disabling
	
public:	
	ATowerSpawnPlaceholder();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	
	#pragma region Towers
	
	UPROPERTY()
	ATowerActor* spawnedTower;

	void SpawnTower(const TSubclassOf<ATowerActor> towerToSpawn);
	bool CanSpawnTower() const;
	bool IsEmpty() const;

	#pragma endregion

	#pragma region Scaffolding

	UPROPERTY(EditDefaultsOnly, Category="References")
	TSubclassOf<ATowerBuildingScaffolding> scaffoldingActorClass;
	
	UPROPERTY()
	ATowerBuildingScaffolding* spawnedScaffolding;

	#pragma endregion
	
	#pragma region Interation

	bool isInInteractionRange;

	UPROPERTY()
	UStaticMeshComponent* placeholderMeshComponent;

	void InitializeInteractions();
	void UpdateInteractionState(bool isInteractionAllowed);

	#pragma endregion
	
	#pragma region Widgets
	
	UPROPERTY()
	UWidgetComponent* InteractEmptyWidgetHolder;

	void InitializeWidgets();
	static void ToggleWidget(UWidgetComponent* widget, bool isActive);
	
	#pragma endregion

	#pragma region TEMP
	
	UFUNCTION(BlueprintCallable)
	void TempInputProcess();

	UPROPERTY(EditDefaultsOnly, Category="Temp")
	TSubclassOf<ATowerActor> TempTowerToPlace;

	UPROPERTY(EditDefaultsOnly, Category="Temp")
	int BuildTime;
	
	#pragma endregion 
};
