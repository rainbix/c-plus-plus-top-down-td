// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Source/Tools/Interpolator.h"
#include "ProgressBarWidget.generated.h"

class UImage;
class UTexture2D;
class UProgressBar;
struct FColor;

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

protected:
	
	virtual void NativeConstruct() override;
	
private:
		
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	#pragma region Progress Bar References
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	UCurveLinearColor* colorCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TArray<float> backgroundTransitionBounds;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TArray<TObjectPtr<UTexture2D>> backgroundTransitionIcons;
	
	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	TObjectPtr<UTexture2D> emptyBarIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Progress Bar")
	FLinearColor unassignedColor;

	#pragma region Animation

	//Temporal reimplementation for default Lerp func
	static float Lerp(const float& A, const float& B, const float Alpha);

	void ProcessAnimation(float deltaTime);

	TUniquePtr<Interpolator<float>> barInterpolator = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Progress Bar")
	float animationTime = 0.2f;

	#pragma endregion
	#pragma endregion

	float maximumVal;
	float currentVal;
	
	void UpdateBarImmediate(float newProgress);
	void UpdateBar(float newProgress);
	TObjectPtr<UTexture2D> GetIcon(float curProgress);
	
	GENERATED_BODY()
};
