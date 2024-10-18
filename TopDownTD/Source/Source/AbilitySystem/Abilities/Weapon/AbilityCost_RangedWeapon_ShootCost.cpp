// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCost_RangedWeapon_ShootCost.h"
#include "Source/Weapons/RangedWeapon.h"
#include "GameplayAbility_WeaponBase.h"

bool UAbilityCost_RangedWeapon_ShootCost::CheckCost(const UGameplayAbility_BaseAbility* Ability,
                                                    const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                    FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Ability, Handle, ActorInfo, OptionalRelevantTags))
	{
		return false;
	}

	if (const UGameplayAbility_WeaponBase* WeaponAbility = Cast<UGameplayAbility_WeaponBase>(Ability))
	{
		if (const ARangedWeapon* Weapon = WeaponAbility->GetWeaponInstance())
		{
			return Weapon->CheckShootCost();			
		}
	}

	return false;
}

void UAbilityCost_RangedWeapon_ShootCost::ApplyCost(const UGameplayAbility_BaseAbility* Ability,
	const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::ApplyCost(Ability, Handle, ActorInfo, ActivationInfo);

	if (const UGameplayAbility_WeaponBase* WeaponAbility = Cast<UGameplayAbility_WeaponBase>(Ability))
	{
		if (const ARangedWeapon* Weapon = WeaponAbility->GetWeaponInstance())
		{
			Weapon->ApplyShootCost();			
		}
	}
}
