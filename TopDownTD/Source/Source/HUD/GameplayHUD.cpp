// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	//world = GetWorld();
	
	//MinimalWidget = CreateWidget<UMinLayoutBase>(world, MinimalLayoutClass);
	//MinimalWidget->AddToViewport();
	//MinimalWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Get a reference to the character, and hook up the stat handlers
	//if (APlayerController* PlayerController = GetOwningPlayerController())
	//	PlayerCharacter = Cast<AMyCppCharacter>(PlayerController->GetPawn());
}

void AGameplayHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//ClearAllHandlers();
	
	Super::EndPlay(EndPlayReason);
}