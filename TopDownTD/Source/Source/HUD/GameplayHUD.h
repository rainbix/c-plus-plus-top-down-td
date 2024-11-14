// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class UScoreWidget;
class UPauseButtonWidget;
class UProgressBarWidget;
class UMinimapWidget;
class UActiveWeaponWidget;
class ULevelStateWidget;
class UHudTestWidget;
class UPauseWidget;
class UTowerShopWidget;
class ATowerActor;
class UMoneyWidget;
class UGameOverWidget;

UCLASS()
class SOURCE_API AGameplayHUD : public AHUD
{
public:

	#pragma region Widget Classes
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMinimapWidget> MinimapWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UActiveWeaponWidget> ActiveWeaponWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UProgressBarWidget> PlayerHealthWidgetClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULevelStateWidget> LevelStateWidgetClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPauseWidget> PauseWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPauseButtonWidget> PauseButtonClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UTowerShopWidget> TowerShopClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMoneyWidget> MoneyWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UScoreWidget> ScoreWidgetClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameOverWidget> GameOverClass = nullptr;
	
	//Test widget
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UHudTestWidget> HudTestWidgetClass = nullptr;

	#pragma endregion 

	#pragma region Tower Shop
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTowerSelected, TSubclassOf<ATowerActor>, int)
	FOnTowerSelected OnTowerBuildRequest;
	
	void ShowTowerShopWidget();
	void ShopTowerClosedHandler(TSubclassOf<ATowerActor> selectedTowerClass, int buildTime, int price) const;

	#pragma endregion 

	#pragma region Pause
	
	void TogglePause();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPauseToggleHandler(bool isPause);

	#pragma endregion 
	
protected:
	UFUNCTION()
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:

	UPROPERTY()
	UWorld* world;
	
	UPROPERTY()
	APlayerController* playerController;

	#pragma region Widgets Instances
	
	UPROPERTY()
	TObjectPtr<UMinimapWidget> minimapWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UActiveWeaponWidget> activeWeaponWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UProgressBarWidget> playerHealthWidget = nullptr;

	UPROPERTY()
	TObjectPtr<ULevelStateWidget> levelStateWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UHudTestWidget> hudTestWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseWidget> pauseWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseButtonWidget> pauseButtonWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UTowerShopWidget> towerShopWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UMoneyWidget> moneyWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UScoreWidget> scoreWidget = nullptr;

	#pragma endregion 

	#pragma region Widgets
	
	void InitializeWidgets();
	void DisposeWidgets();
	
	template <typename T>
	T* SpawnWidget(TSubclassOf<T> widgetClass, bool isCollapsed = false);

	#pragma endregion

	void FinishGame(int score);
	
	GENERATED_BODY()
};
