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
		InitializeWidget(maximumVal, currentVal);
	}
	
	if (propertyName == GET_MEMBER_NAME_CHECKED(UProgressBarWidget, currentVal))
	{
		if (maximumVal <= 0)
			InitializeWidget(maximumVal, currentVal);
		
		SetValueImmediate(currentVal);
	}
}

void UProgressBarWidget::SetValueImmediate(float newVal)
{
	currentVal = newVal;
	
	const float progress = FMath::Clamp(newVal / maximumVal, 0, 1);
	
	UpdateBar(progress);
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

	return TTuple<FLinearColor, TObjectPtr<UTexture2D>>(bar->GetFillColorAndOpacity(), emptyBarIcon);
}

#endif

void UProgressBarWidget::InitializeWidget(int maxVal, int initVal)
{
	this->maximumVal = maxVal;
	this->currentVal = initVal > 0 ? initVal : maxVal;

	SetValueImmediate(currentVal);
}

void UProgressBarWidget::SetValue(int newVal)
{
	UE_LOG(LogTemp, Log, TEXT("SetValue: %d"), newVal);
	
	if (bar)
	{
		currentVal = newVal;

		//TODO: Move to lerp
		const float rawProgress = static_cast<float>(newVal) / maximumVal;
		const float progress = FMath::Clamp(rawProgress, 0, 1);
		
		UpdateBar(progress);
	}
}

void UProgressBarWidget::UpdateBar(float progress)
{
	bar->SetPercent(progress);

	auto translationData = GetTransitionData(progress);
	bar->SetFillColorAndOpacity(translationData.Key);
	barImage->SetBrushFromTexture(translationData.Value);
}

void UProgressBarWidget::Update(float deltaTime)
{
	//TODO: Lerp
}


