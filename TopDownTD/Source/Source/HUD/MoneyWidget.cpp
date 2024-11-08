// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyWidget.h"
#include "Components/TextBlock.h"

void UMoneyWidget::InitializeWidget(int initialAmount)
{
	SetMoney(initialAmount);
}

void UMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	deltaMoneyText->SetVisibility(ESlateVisibility::Hidden);
}

void UMoneyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ProcessTimer(InDeltaTime);
}

void UMoneyWidget::Add(int delta, int amount)
{
	if (deltaMoneyText)
	{
		const FString costStr = FString::Printf(TEXT("+ %d"), delta);
		deltaMoneyText->SetText(FText::FromString(costStr));
		deltaMoneyText->SetVisibility(ESlateVisibility::Visible);
		deltaMoneyText->SetColorAndOpacity(addColor);

		StartTimer();
	}

	SetMoney(amount);
}

void UMoneyWidget::Remove(int delta, int amount)
{
	if (deltaMoneyText)
	{
		const FString costStr = FString::Printf(TEXT("- %d"), delta);
		deltaMoneyText->SetText(FText::FromString(costStr));
		deltaMoneyText->SetVisibility(ESlateVisibility::Visible);
		deltaMoneyText->SetColorAndOpacity(removeColor);

		StartTimer();
	}

	SetMoney(amount);
}

void UMoneyWidget::SetMoney(int newAmount)
{
	if (currentMoneyText)
	{
		const FString costStr = FString::Printf(TEXT("$ %d"), newAmount);
		currentMoneyText->SetText(FText::FromString(costStr));
	}
}

#pragma region Timer

void UMoneyWidget::StartTimer()
{
	curTimerValue = 0;
	bIsTimerActive = true;
}

void UMoneyWidget::StopTimer()
{
	curTimerValue = 0;
	bIsTimerActive = false;
}

void UMoneyWidget::ProcessTimer(float deltaTime)
{
	if (IsTimerActive())
	{
		curTimerValue += deltaTime;
		if (curTimerValue >= timerDuration)
		{
			deltaMoneyText->SetVisibility(ESlateVisibility::Hidden);
			StopTimer();
		}
	}
}

bool UMoneyWidget::IsTimerActive()
{
	return bIsTimerActive;
}

#pragma endregion
