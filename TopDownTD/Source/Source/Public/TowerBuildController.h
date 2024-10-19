// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerBuildController.generated.h"

class ATowerSpawnPlaceholder;
class AGameplayHUD;
class ATowerActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOURCE_API UTowerBuildController : public UActorComponent
{
	//Component is expected to be added onto player controller
	
	GENERATED_BODY()
	
public:
	void RegisterPlaceholder(ATowerSpawnPlaceholder* towerPlaceholder);
	
protected:
	virtual void BeginPlay() override;

private:
	TArray<ATowerSpawnPlaceholder*> TowerSpawnPlaceholders;

	UPROPERTY(EditDefaultsOnly, Category="Temp")
	float BuildTime;
	
	UPROPERTY()
	AGameplayHUD* hud;
	
	UPROPERTY()
	UWorld* world;

	UPROPERTY()
	ATowerSpawnPlaceholder* activePlaceholder;

	//Gets called when corresponding Build button is pressed
	void BuildInputHandler();
	
	//Gets called when user picks a tower in tower shop
	void TowerBuildRequestHandler(TSubclassOf<ATowerActor> selectedTowerClass);
	
	void TryShowTowerShop();
};
