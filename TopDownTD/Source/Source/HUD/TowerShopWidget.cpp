// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShopWidget.h"

#include "GameplayGameState.h"
#include "Source/TowerActor.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Source/Data/TowerShopData.h"
#include "Source/Tools/GeneralPurposeUtils.h"

void UTowerShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeCurrentMoney();
	InitializeButtonHandlers();
	InitializeTowerView(towerAName, towerAPrice, towerABuildTime, TowerAImage, towerAButton, TowerARowName);
	InitializeTowerView(towerBName, towerBPrice, towerBBuildTime, TowerBImage, towerBButton, TowerBRowName);
}

void UTowerShopWidget::InitializeCurrentMoney()
{
	if (currentMoneyText)
	{
		if (const auto gameState = GetWorld()->GetGameState<AGameplayGameState>())
		{
			const FString costStr = FString::Printf(TEXT("$ %d"), gameState->GetCurrentMoney());
			currentMoneyText->SetText(FText::FromString(costStr));
		}
	}
}

void UTowerShopWidget::InitializeButtonHandlers()
{
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

void UTowerShopWidget::InitializeTowerView(UTextBlock* towerName, UTextBlock* towerPrice, UTextBlock* towerBuildTime,
	UImage* towerImage, UButton* towerButton, const FName& rowName)
{
	//Example for iterating over all table
	//TArray<FTowerShopData*> Towers;
	//DataTableHandle.DataTable->GetAllRows("", Towers);
	
	if (const auto towerData = GetTowerDataFromTable(rowName))
	{
		if (towerName)
		{
			towerName->SetText(towerData->TowerName);
		}

		if (towerPrice)
		{
			const FString costStr = FString::Printf(TEXT("$ %d"), towerData->Cost);
			towerPrice->SetText(FText::FromString(costStr));

			//Set proper color depending on whether it is enough money to buy a tower
			if (const auto gameState = GetWorld()->GetGameState<AGameplayGameState>())
			{
				const auto labelColor = gameState->HasEnoughMoney(towerData->Cost) ? EnoughMoneyColor : NotEnoughMoneyColor;
				towerPrice->SetColorAndOpacity(labelColor);
			}
		}

		if (towerBuildTime)
		{
			const FString buildTimeStr = FString::Printf(TEXT("%d sec"), towerData->BuildTime);
			towerBuildTime->SetText(FText::FromString(buildTimeStr));
		}

		if (towerImage && towerData->TowerIcon)
		{
			towerImage->SetBrushFromTexture(towerData->TowerIcon);
		}

		//Tweak a buy button depending on whether it is enough money to buy a tower
		if (towerButton)
		{
			if (const auto gameState = GetWorld()->GetGameState<AGameplayGameState>())
			{
				const bool hasEnoughMoney = gameState->HasEnoughMoney(towerData->Cost);
				
				auto btnColor = towerButton->GetColorAndOpacity();
				btnColor.A = hasEnoughMoney ? 1.0 : 0.75;
		
				towerButton->SetColorAndOpacity(btnColor);
				towerButton->SetIsEnabled(hasEnoughMoney);
			}			
		}
	}
}

void UTowerShopWidget::CloseButtonPressHandler()
{
	OnClosed.Broadcast(nullptr, -1, 0);
}

void UTowerShopWidget::TowerButtonAPressHandler()
{
	BroadCastWithTowerSelection(TowerARowName);
}

void UTowerShopWidget::TowerButtonBPressHandler()
{
	BroadCastWithTowerSelection(TowerBRowName);
}

void UTowerShopWidget::BroadCastWithTowerSelection(const FName& towerRowName) const
{
	const auto towerDataEntry = GetTowerDataFromTable(towerRowName);
	if (towerDataEntry && towerDataEntry->TowerClass)
	{
		OnClosed.Broadcast(towerDataEntry->TowerClass, towerDataEntry->BuildTime, towerDataEntry->Cost);
	}
	else
	{
		if (towerDataEntry == nullptr)
			GeneralPurposeUtils::DisplayScreenMessage("TowerDataEntry not valid", FColor::Red);
		else if (!towerDataEntry->TowerClass)
			GeneralPurposeUtils::DisplayScreenMessage("TowerClass pointer not valid", FColor::Red);
	}
}

const FTowerShopData* UTowerShopWidget::GetTowerDataFromTable(const FName& rowName) const
{
	if (DataTableHandle.DataTable)
		return DataTableHandle.DataTable->FindRow<FTowerShopData>(rowName, "");
	
	return nullptr;
}