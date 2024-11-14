// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayHUD.h"
#include "MinimapWidget.h"
#include "LevelStateWidget.h"
#include "MoneyWidget.h"
#include "PauseButtonWidget.h"
#include "GameOverWidget.h"
#include "HudTestWidget.h"
#include "ActiveWeaponWidget.h"
#include "Source/TowerActor.h"
#include "FWeaponData.h"
#include "GameplayGameState.h"
#include "PauseWidget.h"
#include "PlayerCharacterSource.h"
#include "ProgressBarWidget.h"
#include "ScoreWidget.h"
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
	moneyWidget = SpawnWidget(MoneyWidgetClass);
	scoreWidget = SpawnWidget(ScoreWidgetClass);
	
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
	AGameplayGameState* gameState = GetWorld()->GetGameState<AGameplayGameState>();
	APlayerCharacterSource* sourcePlayerCharacter = Cast<APlayerCharacterSource>(PlayerPawn);
	check(sourcePlayerCharacter);

	if (playerHealthWidget)
	{
		UHealthComponent* HealthComponent = sourcePlayerCharacter->GetHealthComponent();
		
		int maxHealth = HealthComponent->GetMaxHealth();
		int curHealth = HealthComponent->GetCurrentHealth();

		if (HealthComponent->GetIsInitialized())
		{
			playerHealthWidget->InitializeWidget(maxHealth, curHealth);
		}
		else
		{
			HealthComponent->OnComponentInitializeDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::InitializeWidget);
		}
		
		HealthComponent->OnCurrentHealthChangeDelegate.AddUObject(playerHealthWidget, &UProgressBarWidget::SetValue);
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

	if (moneyWidget)
	{
		moneyWidget->InitializeWidget(gameState->GetCurrentMoney());
		gameState->OnMoneyAdded.AddUObject(moneyWidget, &UMoneyWidget::Add);
		gameState->OnMoneyRemoved.AddUObject(moneyWidget, &UMoneyWidget::Remove);
	}
	
	if (scoreWidget)
	{
		scoreWidget->UpdateScore(0, gameState->GetScore());
		gameState->OnScoreAdded.AddUObject(scoreWidget, &UScoreWidget::UpdateScore);
	}

	if(gameState)
	{
		gameState->OnGameFinished.AddUObject(this, &AGameplayHUD::FinishGame);
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
		HealthComponent->OnComponentInitializeDelegate.RemoveAll(playerHealthWidget);
		HealthComponent->OnCurrentHealthChangeDelegate.RemoveAll(playerHealthWidget);
	}

	if (activeWeaponWidget)
	{
		auto WeaponComponent = sourcePlayerCharacter->GetWeaponComponent();

		WeaponComponent->OnWeaponChanged.RemoveAll(activeWeaponWidget);
		WeaponComponent->OnWeaponAmmoChange.RemoveAll(activeWeaponWidget);
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
	playerController->SetPause(true);

	//Show cached widget if it already has been initialized 
	if (towerShopWidget)
	{
		towerShopWidget->AddToViewport();
	}
	else
	{
		//Lazy initialization of Tower Shop Widget
		if (TowerShopClass)
		{
			towerShopWidget = SpawnWidget(TowerShopClass);
			towerShopWidget->OnClosed.AddUObject(this, &AGameplayHUD::ShopTowerClosedHandler);
		}
	}
}

void AGameplayHUD::ShopTowerClosedHandler(TSubclassOf<ATowerActor> selectedTowerClass, int buildTime, int price) const
{
	//Hide widget
	playerController->SetPause(false);
	towerShopWidget->RemoveFromParent();

	//If a tower was chosen (not merely shop closed) broadcast event
	if (selectedTowerClass)
	{
		OnTowerBuildRequest.Broadcast(selectedTowerClass, buildTime);
		
		if (const auto gameState = GetWorld()->GetGameState<AGameplayGameState>())
		{
			gameState->RemoveMoney(price);
		}
	}
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

void AGameplayHUD::FinishGame(int score)
{
	if (const auto gameOverWidget = SpawnWidget(GameOverClass))
	{
		gameOverWidget->InitializeWidget(score);
	}
}

