// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Source/AbilitySystem/Abilities/GameplayAbility_BaseAbility.h"
#include "GameplayAbility_WeaponBase.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_WeaponBase : public UGameplayAbility_BaseAbility
{
	GENERATED_BODY()
public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
								FGameplayTagContainer* OptionalRelevantTags) const override;
protected:
	AWeapon* GetWeaponInstance() const;
};
