// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticipantWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UParticipantWidget::SetParticipantName(FText name)
{
	if(participantName)
		participantName->SetText(name);
}

void UParticipantWidget::SetWidgetVisibility(ESlateVisibility visibility)
{
	if (participantName)
		SetVisibility(visibility);
}

void UParticipantWidget::SetNameStyle(FSlateColor color)
{
	if (participantName)
		participantName->SetColorAndOpacity(color);
}

void UParticipantWidget::SetBackgroundStyle(FLinearColor color)
{
	if (background)
		background->SetBrushColor(color);
}

void UParticipantWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UParticipantWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
