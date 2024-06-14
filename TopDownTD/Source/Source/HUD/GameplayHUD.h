// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class UProgressBarWidget;
class UMinimapWidget;
class UActiveWeaponWidget;
class ULevelStateWidget;
class UHudTestWidget;

UCLASS()
class SOURCE_API AGameplayHUD : public AHUD
{
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMinimapWidget> MinimapWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UActiveWeaponWidget> ActiveWeaponWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UProgressBarWidget> PlayerHealthWidgetClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULevelStateWidget> LevelStateWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UHudTestWidget> HudTestWidgetClass = nullptr;

protected:
	UFUNCTION()
	void TestShoot();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:

	UPROPERTY()
	UWorld* world;
	
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

	template <typename  T>
	T* SpawnWidget(TSubclassOf<T> widgetClass, bool isCollapsed = false);

	void InitializeWidgets();
	
	GENERATED_BODY()
	
};
