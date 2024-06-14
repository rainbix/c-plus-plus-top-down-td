// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"
#include "MinimapWidget.h"
#include "LevelStateWidget.h"
#include "HudTestWidget.h"
#include "ActiveWeaponWidget.h"
#include "FWeaponData.h"
#include "ProgressBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Source/Tools/GeneralPurposeUtils.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	
	minimapWidget = SpawnWidget(MinimapWidgetClass);
	activeWeaponWidget = SpawnWidget(ActiveWeaponWidgetClass);
	levelStateWidget = SpawnWidget(LevelStateWidgetClass);
	playerHealthWidget = SpawnWidget(PlayerHealthWidgetClass);
	hudTestWidget = SpawnWidget(HudTestWidgetClass);

	InitializeWidgets();
}

void AGameplayHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//ClearAllHandlers();
	
	Super::EndPlay(EndPlayReason);
}

void AGameplayHUD::InitializeWidgets()
{
	if (playerHealthWidget)
	{
		//TODO: Replace initialization to character component health when ready
		int maxHealth = 100;
		int curHealth = 80;

		if (hudTestWidget)
		{
			maxHealth = hudTestWidget->MaxHealth;
			curHealth = hudTestWidget->CurHealth;
		}
		
		playerHealthWidget->InitializeWidget(maxHealth, curHealth);
	}

	if (activeWeaponWidget)
		activeWeaponWidget->InitializeWidget(new FWeaponData(100, 75, EWeaponTypes::Weapon1));

	if (hudTestWidget)
	{
		hudTestWidget->OnHealthIncreasedDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
		hudTestWidget->OnHealthDecreasedDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
		hudTestWidget->OnShootDelegate.AddUObject(this, &AGameplayHUD::TestShoot);
	}
}

void AGameplayHUD::TestShoot()
{
	GeneralPurposeUtils::DisplayScreenMessage("Shoot from here");
}


template <typename T>
T* AGameplayHUD::SpawnWidget(TSubclassOf<T> widgetClass, bool isCollapsed)
{
	if (!widgetClass)
		return nullptr;
	
	T* widget = CreateWidget<T>(world, widgetClass);
	if (!widget)
		return nullptr;
	
	widget->AddToViewport();

	if (isCollapsed)
		widget->SetVisibility(ESlateVisibility::Collapsed);
	
	return widget;
}
