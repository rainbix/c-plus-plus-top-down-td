// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_BaseAbility.h"

UGameplayAbility_BaseAbility::UGameplayAbility_BaseAbility()
{
	InputId = EAbilityInputID::None;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

int32 UGameplayAbility_BaseAbility::GetInputId()
{
	return static_cast<int32>(InputId);
}
