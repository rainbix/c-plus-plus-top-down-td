// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Source/UI/CloseWidgetAction.h"
#include "PauseMenuControler_test.generated.h"

class UPauseMenuWidget;

UCLASS()
class SOURCE_API APauseMenuControler_test : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APauseMenuControler_test();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void OpenPauseMenu();

	CloseWidgetAction* closeAction;
	UPauseMenuWidget* PauseMenuWidget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseMenuWidget> pauseMenu;
};
