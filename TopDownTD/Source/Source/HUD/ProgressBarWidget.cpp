// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressBarWidget.h"
#include "Components/Image.h"
#include "Math/Color.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"
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

	if (colorCurve)
		bar->SetFillColorAndOpacity(colorCurve->GetLinearColorValue(newProgress));
	else
		bar->SetFillColorAndOpacity(unassignedColor);
		
	barImage->SetBrushFromTexture( GetIcon(newProgress));
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

TObjectPtr<UTexture2D> UProgressBarWidget::GetIcon(float curProgress)
{
	if (backgroundTransitionBounds.Num() == 0 || curProgress <= 0)
		return emptyBarIcon; 
	
	for (int i = 0; i < backgroundTransitionBounds.Num(); i++)
	{
		if (curProgress > backgroundTransitionBounds[i])
		{
			return backgroundTransitionIcons[i];
		}
	}

	return backgroundTransitionIcons[backgroundTransitionIcons.Num() - 1];
}
