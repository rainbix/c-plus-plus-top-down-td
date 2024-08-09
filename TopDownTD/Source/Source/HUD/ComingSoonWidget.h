// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ComingSoonWidget.generated.h"

UCLASS()
class SOURCE_API UComingSoonWidget : public UUserWidget
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FString titleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FString bodyText;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> titleLabel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> textLabel;
	
	void UpdateTextBlocks();
	
	GENERATED_BODY()
};
