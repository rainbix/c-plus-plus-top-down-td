// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShopWidget.h"
#include "Components/Button.h"
#include "Source/TowerActor.h"
#include "Source/Tools/GeneralPurposeUtils.h"

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
	GeneralPurposeUtils::DisplayScreenMessage("Press button Close");
}

void UTowerShopWidget::TowerButtonAPressHandler()
{
	GeneralPurposeUtils::DisplayScreenMessage("Press button A");
}

void UTowerShopWidget::TowerButtonBPressHandler()
{
	GeneralPurposeUtils::DisplayScreenMessage("Press button B");
}
