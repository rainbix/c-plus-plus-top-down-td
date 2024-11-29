// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Source/AbilitySystem/Abilities/GameplayAbility_BaseAbility.h"
#include "UObject/Object.h"
#include "GameplayAbility_Tower_Base.generated.h"

class ATowerActor;
/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_Tower_Base : public UGameplayAbility_BaseAbility
{
	GENERATED_BODY()

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
							FGameplayTagContainer* OptionalRelevantTags) const override;
	ATowerActor* GetTowerInstance() const;
};
