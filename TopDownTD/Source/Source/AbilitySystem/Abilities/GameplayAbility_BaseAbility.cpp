// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_BaseAbility.h"

#include "AbilityCost.h"
#include "AbilitySystemComponent.h"

UGameplayAbility_BaseAbility::UGameplayAbility_BaseAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationPolicy = EAbilityActivationPolicy::OnInputTriggered;
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

void UGameplayAbility_BaseAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	TryActivateAbility(ActorInfo, Spec);
}

void UGameplayAbility_BaseAbility::TryActivateAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{
	if (ActivationPolicy != EAbilityActivationPolicy::OnSpawn) return;

	if (ActorInfo && !Spec.IsActive())
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (ASC)
		{
			ASC->TryActivateAbility(Spec.Handle);
		}
	}
}
