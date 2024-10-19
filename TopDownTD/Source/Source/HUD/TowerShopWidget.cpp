// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShopWidget.h"
#include "Components/Button.h"

void UTowerShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (closeButton)
	{
		closeButton->OnClicked.Clear();
		closeButton->OnClicked.AddDynamic(this, &UTowerShopWidget::CloseButtonPressHandler);
	}

	if (towerAButton)
	{
		towerAButton->OnClicked.Clear();
		towerAButton->OnClicked.AddDynamic(this, &UTowerShopWidget::TowerButtonAPressHandler);
	}

	if (towerBButton)
	{
		towerBButton->OnClicked.Clear();
		towerBButton->OnClicked.AddDynamic(this, &UTowerShopWidget::TowerButtonBPressHandler);
	}
}

void UTowerShopWidget::CloseButtonPressHandler()
{
	OnClosed.Broadcast(nullptr);
}

void UTowerShopWidget::TowerButtonAPressHandler()
{
	OnClosed.Broadcast(TempTowerToPlaceA);
}

void UTowerShopWidget::TowerButtonBPressHandler()
{
	OnClosed.Broadcast(TempTowerToPlaceB);
}
