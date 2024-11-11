// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_WeaponBase.h"
#include "GameplayAbility_Weapon_Reload.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_Weapon_Reload : public UGameplayAbility_WeaponBase
{
	GENERATED_BODY()

public:
	UGameplayAbility_Weapon_Reload();

protected:
	UPROPERTY(EditAnywhere)
	float ReloadTime = 1.0f;
	
	UFUNCTION()
	void OnCompleted();
	UFUNCTION()
	void OnCancelled();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	
};
