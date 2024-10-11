// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_WeaponBase.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Weapon_Fire.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS()
class SOURCE_API UGameplayAbility_Weapon_Fire : public UGameplayAbility_WeaponBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parameters")
	float TraceMaxDistance = 5000.0f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> AppliedEffects;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* FireHipMontage = nullptr;

	UPROPERTY(EditAnywhere)
	float FireDelay = 1.0f;

public:
	UGameplayAbility_Weapon_Fire();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void OnCompleted();
	UFUNCTION()
	void OnCancelled();
	virtual void OnFire();
};
