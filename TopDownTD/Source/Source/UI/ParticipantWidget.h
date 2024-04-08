// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParticipantWidget.generated.h"

class UTextBlock;
class UBorder;

UCLASS(Abstract)
class SOURCE_API UParticipantWidget : public UUserWidget
{
public:
	void SetParticipantName(FText name);
	void SetWidgetVisibility(ESlateVisibility visibility);
	void SetNameStyle(FSlateColor color);
	void SetBackgroundStyle(FLinearColor color);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* participantName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* background;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	GENERATED_BODY()
};
