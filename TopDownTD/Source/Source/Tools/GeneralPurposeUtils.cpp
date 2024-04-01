// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralPurposeUtils.h"

void GeneralPurposeUtils::DisplayScreenMessage(const FString& message, FColor color, float duration)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, duration, color, message);
}
