// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudTestWidget.generated.h"

UCLASS()
class SOURCE_API UHudTestWidget : public UUserWidget
{
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthInitialize, int)
	FOnHealthInitialize OnHealthInitializeDelegate;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthIncreased, int)
	FOnHealthIncreased OnHealthIncreasedDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthDecreased, int)
	FOnHealthIncreased OnHealthDecreasedDelegate;

	DECLARE_MULTICAST_DELEGATE(FOnShoot)
	FOnShoot OnShootDelegate;
	
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(int amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseHealth(int amount);

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int CurHealth = 75;
	
private:
	GENERATED_BODY()
	
};
