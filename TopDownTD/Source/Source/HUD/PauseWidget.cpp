// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "GameplayHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (resumeButton)
	{
		resumeButton->OnClicked.Clear();
		resumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeButtonPressHandler);
	}

	if (mainMenuButton)
	{
		mainMenuButton->OnClicked.Clear();
		mainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::MainMenuButtonPressHandler);
	}

	if (quitButton)
	{
		quitButton->OnClicked.Clear();
		quitButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitButtonPressHandler);
	}
}

void UPauseWidget::ResumeButtonPressHandler()
{
	const APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (AGameplayHUD* hud = Cast<AGameplayHUD>(playerController->GetHUD()))
	{
		hud->TogglePause();	
	}
}

void UPauseWidget::MainMenuButtonPressHandler()
{
	if (mainMenuLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), mainMenuLevel);
	else
		ResumeButtonPressHandler();
}

void UPauseWidget::QuitButtonPressHandler()
{
	GetOwningPlayer()->ConsoleCommand("exit");
}
