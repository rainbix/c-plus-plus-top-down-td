// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayAbilitySpec.h"
#include "AbilityCost.generated.h"

class UGameplayAbility_BaseAbility;
/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UAbilityCost : public UObject
{
	GENERATED_BODY()

public:
	UAbilityCost() { }

	virtual bool CheckCost(const UGameplayAbility_BaseAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,  FGameplayTagContainer* OptionalRelevantTags) const
	{
		return true;
	}
	
	virtual void ApplyCost(const UGameplayAbility_BaseAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
	{
	}
};
