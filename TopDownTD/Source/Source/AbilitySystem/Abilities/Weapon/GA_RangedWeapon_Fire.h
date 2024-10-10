// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_RangedWeapon_Fire.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS()
class SOURCE_API UGA_RangedWeapon_Fire : public UGameplayAbility
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
	UGA_RangedWeapon_Fire();
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	                                FGameplayTagContainer* OptionalRelevantTags) const override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	AWeapon* GetWeaponInstance() const;
	UFUNCTION()
	void OnCompleted();
	UFUNCTION()
	void OnCancelled();
	virtual void OnFire();
};
