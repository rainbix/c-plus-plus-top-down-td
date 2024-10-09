// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class SOURCE_API UPauseWidget : public UUserWidget
{
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* resumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* mainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* quitButton;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* mainMenuLevel;

protected:
	virtual auto NativeConstruct() -> void override;
	
private:
	UFUNCTION()
	void ResumeButtonPressHandler();
	
	UFUNCTION()
	void MainMenuButtonPressHandler();

	UFUNCTION()
	void QuitButtonPressHandler();
	
	GENERATED_BODY()
	
};
