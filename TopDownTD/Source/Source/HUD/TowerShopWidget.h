// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerShopWidget.generated.h"

class UButton;
class ATowerActor;

UCLASS()
class SOURCE_API UTowerShopWidget : public UUserWidget
{
	//Purpose of the class is to show and handle tower shop

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTowerSelected, TSubclassOf<ATowerActor> selectedTower)
	FOnTowerSelected OnTowerSelected;

	DECLARE_MULTICAST_DELEGATE(FOnClosed)
	FOnClosed OnClosed;

protected:
	virtual void NativeConstruct() override;
	
private:

	#pragma region Buttons
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* closeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* towerAButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* towerBButton;

	#pragma endregion 
	
	#pragma region ButtonHandlers
	
	UFUNCTION()
	void CloseButtonPressHandler();
	
	UFUNCTION()
	void TowerButtonAPressHandler();
	
	UFUNCTION()
	void TowerButtonBPressHandler();

#pragma endregion 

#pragma region TEMP
	
	//TODO: TO be replaced by config file params
	UPROPERTY(EditDefaultsOnly, Category="Temp")
	TSubclassOf<ATowerActor> TempTowerToPlaceA;

	//TODO: TO be replaced by config file params
	UPROPERTY(EditDefaultsOnly, Category="Temp")
	TSubclassOf<ATowerActor> TempTowerToPlaceB;

#pragma endregion 
	
	GENERATED_BODY()
};
