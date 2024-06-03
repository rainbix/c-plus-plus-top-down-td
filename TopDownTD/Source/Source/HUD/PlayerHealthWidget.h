// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthWidget.generated.h"

class UProgressBarWidget;

UCLASS()
class SOURCE_API UPlayerHealthWidget : public UUserWidget
{
public:
	UPROPERTY(EditDefaultsOnly, Category="Wdigets")
	TObjectPtr<UProgressBarWidget> playerProgressBarWidget;

	void Initialize(float maxVal, float initVal = -1);

private:
	GENERATED_BODY()
};
