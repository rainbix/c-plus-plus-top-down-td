// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthWidget.h"
#include "ProgressBarWidget.h"

void UPlayerHealthWidget::Initialize(float maxVal, float initVal)
{
	if (playerProgressBarWidget)
		playerProgressBarWidget->Initialize(maxVal, initVal);
}
