// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerShopWidget.generated.h"

class UButton;
class ATowerActor;
class UTextBlock;
class UImage;
struct FTowerShopData;

UCLASS()
class SOURCE_API UTowerShopWidget : public UUserWidget
{
	//Purpose of the class is to show and handle tower shop

public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnClosed, TSubclassOf<ATowerActor>, int, int)
	FOnClosed OnClosed;

protected:
	virtual void NativeConstruct() override;
	
private:

	#pragma region Current Money
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* currentMoneyText;

	void InitializeCurrentMoney();
	
	#pragma endregion 

	#pragma region Tower View Data

	UPROPERTY(EditDefaultsOnly, Category="Towers")
	FLinearColor EnoughMoneyColor;
	
	UPROPERTY(EditDefaultsOnly, Category="Towers")
	FLinearColor NotEnoughMoneyColor;
	
	//Tower A
	UPROPERTY(EditDefaultsOnly, Category="Towers")
	FName TowerARowName;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerAName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerAPrice;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerABuildTime;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* TowerAImage;

	//Tower B
	UPROPERTY(EditDefaultsOnly, Category="Towers")
	FName TowerBRowName;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerBName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerBPrice;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* towerBBuildTime;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* TowerBImage;

	void InitializeTowerView(UTextBlock* toweName, UTextBlock* towerPrice, UTextBlock* towerBuildTime,
		UImage* towerImage, UButton* towerButton, const FName& rowName);
	
	#pragma endregion 
	
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
	void InitializeButtonHandlers();
	
	UFUNCTION()
	void CloseButtonPressHandler();
	
	UFUNCTION()
	void TowerButtonAPressHandler();
	
	UFUNCTION()
	void TowerButtonBPressHandler();

#pragma endregion 

	#pragma region Data
	
	UPROPERTY(EditDefaultsOnly, Category="Data", meta=(RowType="TowerShopData"))
	FDataTableRowHandle DataTableHandle;

	void BroadCastWithTowerSelection(const FName& towerRowName) const;
	const FTowerShopData* GetTowerDataFromTable(const FName& rowName) const;
	
	#pragma endregion 
	
	GENERATED_BODY()
};
