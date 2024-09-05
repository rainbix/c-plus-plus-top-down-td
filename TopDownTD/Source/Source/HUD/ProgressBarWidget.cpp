// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressBarWidget.h"
#include "Components/Image.h"
#include "Math/Color.h"
#include "Components/ProgressBar.h"
#include "Source/Tools/Interpolator.cpp"

#pragma region Native

void UProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	barInterpolator = MakeUnique<Interpolator<float>>(animationTime, 0, 1);
}

void UProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ProcessAnimation(InDeltaTime);
}

#pragma endregion 

void UProgressBarWidget::InitializeWidget(int maxVal, int initVal)
{
	this->maximumVal = maxVal;
	this->currentVal = initVal > 0 ? initVal : maxVal;

	UpdateBarImmediate(currentVal);
}

//Set value with animation (called from outside when Widget is updated)
void UProgressBarWidget::SetValue(int newVal)
{
	if (bar)
	{
		currentVal = newVal;

		const float newRawProgress = static_cast<float>(newVal) / maximumVal;
		const float newProgress = FMath::Clamp(newRawProgress, 0, 1);

		const float curProgress = bar->GetPercent();
		
		barInterpolator->SetFromTo(curProgress, newProgress);
		barInterpolator->Start();
	}
}

// Set value without animation
void UProgressBarWidget::UpdateBarImmediate(float newProgress)
{
	currentVal = newProgress;
	
	const float progress = FMath::Clamp(newProgress / maximumVal, 0, 1);
	
	UpdateBar(progress);
}

void UProgressBarWidget::UpdateBar(float newProgress)
{
	bar->SetPercent(newProgress);
	
	const auto translationData = GetTransitionData(newProgress);
	bar->SetFillColorAndOpacity(translationData.Key);
	barImage->SetBrushFromTexture(translationData.Value);
}

void UProgressBarWidget::ProcessAnimation(float deltaTime)
{
	if (barInterpolator && barInterpolator->IsActive())
	{
		barInterpolator->ProcessTick(deltaTime);
		
		const float progress = barInterpolator->Lerp(Lerp);
		UpdateBar(progress);
		
		if (barInterpolator->IsElapsed())
		{
			barInterpolator->Stop();
			UpdateBar(barInterpolator->To);
		}
	}
}


float UProgressBarWidget::Lerp(const float& A, const float& B, const float Alpha)
{
	return A + Alpha * (B-A);
}

TTuple<FLinearColor, TObjectPtr<UTexture2D>> UProgressBarWidget::GetTransitionData(float curProgress)
{
	if (backgroundTransitionBounds.Num() == 0 || backgroundTransitionColors.Num() == 0 || backgroundTransitionBounds.Num() != backgroundTransitionColors.Num())
		return TTuple<FLinearColor, TObjectPtr<UTexture2D>>(bar->GetFillColorAndOpacity(), emptyBarIcon); 

	if (curProgress <= 0)
	{
		return TTuple<FLinearColor, TObjectPtr<UTexture2D>>(emptyBarColor, emptyBarIcon);
	}
	
	for (int i = 0; i < backgroundTransitionBounds.Num(); i++)
	{
		if (curProgress > backgroundTransitionBounds[i])
		{
			return TTuple<FLinearColor, TObjectPtr<UTexture2D>>( backgroundTransitionColors[i], backgroundTransitionIcons[i]);
		}
	}

	return TTuple<FLinearColor, TObjectPtr<UTexture2D>>(bar->GetFillColorAndOpacity(), backgroundTransitionIcons[backgroundTransitionIcons.Num() - 1]);
}

#if WITH_EDITOR

void UProgressBarWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName propertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (propertyName == GET_MEMBER_NAME_CHECKED(UProgressBarWidget, maximumVal))
	{
		InitializeWidget(maximumVal, currentVal);
	}
	
	if (propertyName == GET_MEMBER_NAME_CHECKED(UProgressBarWidget, currentVal))
	{
		if (maximumVal <= 0)
			InitializeWidget(maximumVal, currentVal);
		
		UpdateBarImmediate(currentVal);
	}
}

#endif


