// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidget.generated.h"

class UImage;
struct FColor;
class UProgressBar;
class UTexture2D;

UCLASS()
class SOURCE_API UProgressBarWidget : public UUserWidget
{
public:
	// References
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> bar;

	// References
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> barImage;
	
	// Methods
	void InitializeWidget(int maxVal, int initVal = -1);
	void SetValue(int newVal);

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
	TArray<TObjectPtr<UTexture2D>> backgroundTransitionIcons;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	FLinearColor emptyBarColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TObjectPtr<UTexture2D> emptyBarIcon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	float maximumVal;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	float currentVal;
	
	void Update(float deltaTime);
	void SetValueImmediate(float newVal);
	void UpdateBar(float progress);
	TTuple<FLinearColor, TObjectPtr<UTexture2D>> GetTransitionData(float curProgress);
	
	GENERATED_BODY()
};
