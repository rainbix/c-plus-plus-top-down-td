// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Source/AbilitySystem/Abilities/AbilityCost.h"
#include "UObject/Object.h"
#include "AbilityCost_RangedWeapon_ShootCost.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, DisplayName="WeaponAmmo")
class SOURCE_API UAbilityCost_RangedWeapon_ShootCost : public UAbilityCost
{
	GENERATED_BODY()

public:
	virtual bool CheckCost(const UGameplayAbility_BaseAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ApplyCost(const UGameplayAbility_BaseAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	UPROPERTY()
	int ConsumedAmmoCount;
};
