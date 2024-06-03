// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressBarWidget.h"
#include "Components/Image.h"
#include "Math/Color.h"
#include "Components/ProgressBar.h"

#pragma region Native

void UProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//TODO: Create interpolator
}

void UProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Update(InDeltaTime);
}

#pragma endregion 

#if WITH_EDITOR

void UProgressBarWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName propertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (propertyName == GET_MEMBER_NAME_CHECKED(UProgressBarWidget, maximumVal))
	{
		Initialize(maximumVal, currentVal);
	}
	
	if (propertyName == GET_MEMBER_NAME_CHECKED(UProgressBarWidget, currentVal))
	{
		if (maximumVal <= 0)
			Initialize(maximumVal, currentVal);
		
		SetValueImmediate(currentVal);
	}
}

void UProgressBarWidget::SetValueImmediate(float newVal)
{
	currentVal = newVal;
	
	const float progress = FMath::Clamp(newVal / maximumVal, 0, 1);
	bar->SetPercent(progress);
	bar->SetFillColorAndOpacity(GetTransitionColor(progress));
}

FLinearColor UProgressBarWidget::GetTransitionColor(float curProgress)
{
	if (backgroundTransitionBounds.Num() == 0 || backgroundTransitionColors.Num() == 0 || backgroundTransitionBounds.Num() != backgroundTransitionColors.Num())
		return bar->GetFillColorAndOpacity();

	for (int i = 0; i < backgroundTransitionBounds.Num(); i++)
	{
		if (curProgress > backgroundTransitionBounds[i])
		{
			return backgroundTransitionColors[i];
		}
	}

	return bar->GetFillColorAndOpacity();
}

#endif

void UProgressBarWidget::Initialize(float maxVal, float initVal)
{
	this->maximumVal = maxVal;
	this->currentVal = initVal > 0 ? initVal : maxVal;

	SetValueImmediate(currentVal);
}

void UProgressBarWidget::SetValue(float newVal)
{
	UE_LOG(LogTemp, Log, TEXT("SetValue: %f"), newVal);
	
	if (bar)
	{
	
		currentVal = newVal;

		//TODO: Move to lerp
		float progress = FMath::Clamp(newVal / maximumVal, 0, 1);
		bar->SetPercent(progress);
	}
}

void UProgressBarWidget::Update(float deltaTime)
{
	//TODO: Lerp
}


