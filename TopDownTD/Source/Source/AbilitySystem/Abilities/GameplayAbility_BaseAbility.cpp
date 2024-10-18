// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_BaseAbility.h"

#include "AbilityCost.h"

UGameplayAbility_BaseAbility::UGameplayAbility_BaseAbility()
{
	InputId = EAbilityInputID::None;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

int32 UGameplayAbility_BaseAbility::GetInputId()
{
	return static_cast<int32>(InputId);
}

bool UGameplayAbility_BaseAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags))
	{
		return false;
	}

	for (TObjectPtr<UAbilityCost> AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost == nullptr) continue;
		if (!AdditionalCost->CheckCost(this, Handle, ActorInfo, OptionalRelevantTags)) return false;
	}

	return true;
}

void UGameplayAbility_BaseAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	check(ActorInfo);

	for (TObjectPtr<UAbilityCost> AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost == nullptr) continue;

		AdditionalCost->ApplyCost(this, Handle, ActorInfo, ActivationInfo);
	}
}
