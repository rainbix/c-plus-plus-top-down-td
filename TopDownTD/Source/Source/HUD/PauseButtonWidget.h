// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseButtonWidget.generated.h"

class UButton;

UCLASS()
class SOURCE_API UPauseButtonWidget : public UUserWidget
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnPause)
	FOnPause OnPauseDelegate;
	
protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> pauseButton;

	UFUNCTION()
	void PauseButtonPressHandler();
	
	GENERATED_BODY()
};
