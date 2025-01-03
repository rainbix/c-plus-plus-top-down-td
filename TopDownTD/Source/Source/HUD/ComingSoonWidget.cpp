// Fill out your copyright notice in the Description page of Project Settings.


#include "ComingSoonWidget.h"

#if WITH_EDITOR
void UComingSoonWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UComingSoonWidget, titleText) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UComingSoonWidget, bodyText))
	{
		UpdateTextBlocks();
	}
}
#endif

void UComingSoonWidget::UpdateTextBlocks()
{
	if (titleLabel)
	{
		titleLabel->SetText(FText::FromString(titleText));
	}

	if (textLabel)
	{
		textLabel->SetText(FText::FromString(bodyText));
	}
}
