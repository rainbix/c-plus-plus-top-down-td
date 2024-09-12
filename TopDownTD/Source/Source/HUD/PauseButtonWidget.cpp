// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseButtonWidget.h"
#include "Components/Button.h"

void UPauseButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (pauseButton)
	{
		pauseButton->OnClicked.AddDynamic(this, &UPauseButtonWidget::PauseButtonPressHandler);			
	}
}

void UPauseButtonWidget::PauseButtonPressHandler()
{
	OnPauseDelegate.Broadcast();
}
