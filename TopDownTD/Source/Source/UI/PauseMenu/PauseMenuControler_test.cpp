// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuControler_test.h"
#include "PauseMenuWidget.h"
#include "Source/UI/CloseWidgetAction.h"


// Sets default values
APauseMenuControler_test::APauseMenuControler_test()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APauseMenuControler_test::BeginPlay()
{
	Super::BeginPlay();

	OpenPauseMenu();
}

void APauseMenuControler_test::OpenPauseMenu()
{
	if(!pauseMenu)
	{
		return;
	}

	
	PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetGameInstance(), pauseMenu);

	if(!PauseMenuWidget)
	{
		return;
	}
	
	PauseMenuWidget->AddToViewport();

	closeAction = new CloseWidgetAction(PauseMenuWidget);

	PauseMenuWidget->Show(closeAction);
}

// Called every frame
void APauseMenuControler_test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

