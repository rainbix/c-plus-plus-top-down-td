// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Tower_Base.h"
#include "UObject/Object.h"
#include "GameplayAbility_Tower_ProjectileFire.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_Tower_ProjectileFire : public UGameplayAbility_Tower_Base
{
	GENERATED_BODY()

public:
	UGameplayAbility_Tower_ProjectileFire();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Parameters")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category="Parameters")
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Parameters")
	TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

	UPROPERTY(EditDefaultsOnly, Category="Parameters")
	FName ShootPointSocketName;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	void OnDelayCompleted();
	void Fire();
};
