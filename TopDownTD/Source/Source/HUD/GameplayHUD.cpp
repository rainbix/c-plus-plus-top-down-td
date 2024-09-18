// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"
#include "MinimapWidget.h"
#include "LevelStateWidget.h"
#include "PauseButtonWidget.h"
#include "HudTestWidget.h"
#include "ActiveWeaponWidget.h"
#include "FWeaponData.h"
#include "PauseWidget.h"
#include "ProgressBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	playerController = UGameplayStatics::GetPlayerController(world, 0);
	
	minimapWidget = SpawnWidget(MinimapWidgetClass);
	activeWeaponWidget = SpawnWidget(ActiveWeaponWidgetClass);
	levelStateWidget = SpawnWidget(LevelStateWidgetClass);
	playerHealthWidget = SpawnWidget(PlayerHealthWidgetClass);
	pauseButtonWidget = SpawnWidget(PauseButtonClass);

	//TODO: Test widget. Remove after all widget bindings are done
	hudTestWidget = SpawnWidget(HudTestWidgetClass);
	
	InitializeWidgets();
}

void AGameplayHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DisposeWidgets();
	
	Super::EndPlay(EndPlayReason);
}

void AGameplayHUD::InitializeWidgets()
{
	if (playerHealthWidget)
	{
		//TODO: Replace initialization with character component health when ready
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
	{
		//TODO: Replace initialization with character component weapon when ready
		int maxAmmo = 100;
		int curAmmo = 10;
		EWeaponTypes weaponType = EWeaponTypes::Weapon1;
		FWeaponData* weaponData = new FWeaponData(maxAmmo, curAmmo, weaponType);
		
		if (hudTestWidget)
		{
			weaponData = hudTestWidget->GetActiveWeaponData();
		}
		
		activeWeaponWidget->InitializeWidget(weaponData);
	}

	if (pauseButtonWidget)
	{
		pauseButtonWidget->OnPauseDelegate.AddUObject(this, &AGameplayHUD::TogglePause);
	}
	
	if (hudTestWidget)
	{
		hudTestWidget->OnHealthIncreasedDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
		hudTestWidget->OnHealthDecreasedDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
		hudTestWidget->OnShootDelegate.AddUObject(activeWeaponWidget, &UActiveWeaponWidget::HandleShoot);
		hudTestWidget->OnReloadDelegate.AddUObject(activeWeaponWidget, &UActiveWeaponWidget::HandleReload);
		hudTestWidget->OnWeaponChangeDelegate.AddUObject(activeWeaponWidget, &UActiveWeaponWidget::HandleWeaponChange);
		hudTestWidget->OnPauseDelegate.AddUObject(this, &AGameplayHUD::TogglePause);
	}
}

void AGameplayHUD::DisposeWidgets()
{
	if (pauseButtonWidget)
	{
		pauseButtonWidget->OnPauseDelegate.RemoveAll(this);
	}
	
	if (hudTestWidget)
	{
		hudTestWidget->OnHealthIncreasedDelegate.RemoveAll(playerHealthWidget);
		hudTestWidget->OnHealthDecreasedDelegate.RemoveAll(playerHealthWidget);
		hudTestWidget->OnShootDelegate.RemoveAll(activeWeaponWidget);
		hudTestWidget->OnReloadDelegate.RemoveAll(activeWeaponWidget);
		hudTestWidget->OnWeaponChangeDelegate.RemoveAll(activeWeaponWidget);
		hudTestWidget->OnPauseDelegate.RemoveAll(this);
	}
}

void AGameplayHUD::TogglePause()
{
	//Enter pause
	if (!playerController->IsPaused()) 
	{
		//Show widget
		if (!pauseWidget)
			pauseWidget = SpawnWidget(PauseWidgetClass);
		else
			pauseWidget->AddToViewport();
	}
	//Exit pause
	else 
	{
		//Hide widget
		if (pauseWidget)
			pauseWidget->RemoveFromParent();
	}

	playerController->SetPause(!playerController->IsPaused());

	//Expose pause function to blueprints
	OnPauseToggleHandler(playerController->IsPaused());
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
