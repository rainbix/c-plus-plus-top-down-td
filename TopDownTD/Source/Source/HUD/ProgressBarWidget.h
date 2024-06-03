// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidget.generated.h"

class UImage;
struct FColor;
class UProgressBar;

UCLASS()
class SOURCE_API UProgressBarWidget : public UUserWidget
{
public:
	// References
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> bar;

	// Methods
	void Initialize(float maxVal, float initVal = -1);
	void SetValue(float newVal);

#if WITH_EDITOR
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif
	
protected:
	
	virtual void NativeConstruct() override;
	
private:
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TArray<float> backgroundTransitionBounds;

	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TArray<FLinearColor> backgroundTransitionColors;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	float maximumVal;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	float currentVal;
	
	void Update(float deltaTime);
	void SetValueImmediate(float newVal);
	FLinearColor GetTransitionColor(float curProgress);
	
	GENERATED_BODY()
};
