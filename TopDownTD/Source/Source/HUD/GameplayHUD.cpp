// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"
#include "MinimapWidget.h"
#include "LevelStateWidget.h"
#include "PauseButtonWidget.h"
#include "HudTestWidget.h"
#include "ActiveWeaponWidget.h"
#include "Source/TowerActor.h"
#include "FWeaponData.h"
#include "PauseWidget.h"
#include "PlayerCharacterSource.h"
#include "ProgressBarWidget.h"
#include "TowerShopWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Source/Health/HealthComponent.h"
#include "Source/Weapons/WeaponComponent.h"

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

#pragma region Widgets

void AGameplayHUD::InitializeWidgets()
{
	APawn* PlayerPawn = playerController->AcknowledgedPawn;
	APlayerCharacterSource* sourcePlayerCharacter = Cast<APlayerCharacterSource>(PlayerPawn);
	check(sourcePlayerCharacter);

	if (playerHealthWidget)
	{
		UHealthComponent* HealthComponent = sourcePlayerCharacter->GetHealthComponent();
		
		int maxHealth = HealthComponent->GetMaxHealth();
		int curHealth = HealthComponent->GetCurrentHealth();
		
		playerHealthWidget->InitializeWidget(maxHealth, curHealth);
		
		HealthComponent->OnHealthChangeDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
	}

	if (activeWeaponWidget)
	{
		UWeaponComponent* WeaponComponent = sourcePlayerCharacter->GetWeaponComponent();

		WeaponComponent->OnWeaponChanged.AddUObject(activeWeaponWidget, &UActiveWeaponWidget::HandleWeaponChange);
		WeaponComponent->OnWeaponAmmoChange.AddUObject(activeWeaponWidget, &UActiveWeaponWidget::HandleWeaponAmmoChanged);

		if (auto Weapon = WeaponComponent->GetCurrentWeapon())
		{
			activeWeaponWidget->InitializeWidget(Weapon);
		}
	}

	if (pauseButtonWidget)
	{
		pauseButtonWidget->OnPauseDelegate.AddUObject(this, &AGameplayHUD::TogglePause);
	}
	
	if (hudTestWidget)
	{
		hudTestWidget->OnPauseDelegate.AddUObject(this, &AGameplayHUD::TogglePause);
	}
}

void AGameplayHUD::DisposeWidgets()
{
	APlayerCharacterSource* sourcePlayerCharacter = Cast<APlayerCharacterSource>(playerController->AcknowledgedPawn);
	check(sourcePlayerCharacter);
	
	if (pauseButtonWidget)
	{
		pauseButtonWidget->OnPauseDelegate.RemoveAll(this);
	}

	if (playerHealthWidget)
	{
		auto HealthComponent = sourcePlayerCharacter->GetHealthComponent();
		HealthComponent->OnHealthChangeDelegate.RemoveAll(playerHealthWidget);
	}

	if (activeWeaponWidget)
	{
		auto WeaponComponent = sourcePlayerCharacter->GetWeaponComponent();

		WeaponComponent->OnWeaponChanged.RemoveAll(activeWeaponWidget);
		WeaponComponent->OnWeaponAmmoChange.RemoveAll(activeWeaponWidget);
	}
	
	if (hudTestWidget)
	{
		hudTestWidget->OnPauseDelegate.RemoveAll(this);
	}
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

#pragma endregion

#pragma region Tower Shop

void AGameplayHUD::ShowTowerShopWidget()
{
	if (towerShopWidget)
	{
		towerShopWidget->AddToViewport();
	}
	else
	{
		if (TowerShopClass)
		{
			towerShopWidget = SpawnWidget(TowerShopClass);
			towerShopWidget->OnClosed.AddUObject(this, &AGameplayHUD::ShopTowerClosed);
			towerShopWidget->OnTowerSelected.AddUObject(this, &AGameplayHUD::ShopTowerSelected);
		}
	}
}

void AGameplayHUD::ShopTowerClosed()
{
	towerShopWidget->RemoveFromParent();
}

void AGameplayHUD::ShopTowerSelected(TSubclassOf<ATowerActor> selectedTowerClass)
{
	if (selectedTowerClass)
		OnTowerBuildRequest.Broadcast(selectedTowerClass);
}

#pragma endregion

#pragma region Pause

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

#pragma endregion 

