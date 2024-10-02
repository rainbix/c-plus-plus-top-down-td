// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

UHealthAttributeSet::UHealthAttributeSet() :
	CurrentHealth(100),
	MaxHealth(100)
{
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		OnMaxHealthChanged.Broadcast(GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		OnCurrentHealthChanged.Broadcast(GetCurrentHealth());
	}
}