// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenuWidget.h"
#include "Source/UI/IClickAction.h"

void UPauseMenuWidget::Show(IClickAction* onClickAction)
{
	m_onClickAction = onClickAction;
}

void UPauseMenuWidget::Resume() const
{
	UE_LOG(LogTemp, Log, TEXT("Resume"));
	if(m_onClickAction != nullptr)
	{
		m_onClickAction->OnClickAction();
	}
}

void UPauseMenuWidget::GoMainMenu() const
{
	UE_LOG(LogTemp, Log, TEXT("GoMainMenu"));
	if(m_onClickAction != nullptr)
	{
		m_onClickAction->OnClickAction();
	}
}
