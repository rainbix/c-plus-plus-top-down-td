// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_WeaponBase.h"
#include "UObject/Object.h"
#include "GameplayAbility_Weapon_AutoReload.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_Weapon_AutoReload : public UGameplayAbility_WeaponBase
{
	GENERATED_BODY()
public:
	UGameplayAbility_Weapon_AutoReload();

protected:
	UPROPERTY(EditDefaultsOnly)
	float CheckInterval = 0.25f;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void PeriodicCheck();
	UFUNCTION()
	void CheckReloadRequired();
};
