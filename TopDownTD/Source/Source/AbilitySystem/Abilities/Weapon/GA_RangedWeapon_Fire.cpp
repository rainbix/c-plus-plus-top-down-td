﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_RangedWeapon_Fire.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/Weapons/Weapon.h"

UGA_RangedWeapon_Fire::UGA_RangedWeapon_Fire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UGA_RangedWeapon_Fire::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                               const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	if(bResult)
	{
		if(GetWeaponInstance() == nullptr)
		{
			//TODO: add log
			bResult = false;	
		}
	}

	return bResult;
}

void UGA_RangedWeapon_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(FireHipMontage)
	{
		UAbilityTask_PlayMontageAndWait* abilityTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FireHipMontage, 1.0f, NAME_None, false, 1.0f);

		abilityTask->OnBlendOut.AddDynamic(this, &ThisClass::OnCompleted);
		abilityTask->OnCompleted.AddDynamic(this, &ThisClass::OnCompleted);
		abilityTask->OnInterrupted.AddDynamic(this, &ThisClass::OnCancelled);
		abilityTask->OnCancelled.AddDynamic(this, &ThisClass::OnCancelled);
		abilityTask->ReadyForActivation();
	} else
	{
		UAbilityTask_WaitDelay* waitDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, FireDelay);
		waitDelayTask->OnFinish.AddDynamic(this, &ThisClass::OnCompleted);
		waitDelayTask->ReadyForActivation();
	}

	OnFire();
}

void UGA_RangedWeapon_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

AWeapon* UGA_RangedWeapon_Fire::GetWeaponInstance() const
{
	if (FGameplayAbilitySpec* Spec =  GetCurrentAbilitySpec())
	{
		return Cast<AWeapon>(Spec->SourceObject.Get());
	}

	return nullptr;
}

void UGA_RangedWeapon_Fire::OnCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	
}

void UGA_RangedWeapon_Fire::OnCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
}

void UGA_RangedWeapon_Fire::OnFire()
{
	AWeapon* Weapon = GetWeaponInstance();

	FVector StartPosition = Weapon->GetShootStartPosition();
	FVector Direction = Weapon->GetShootDirection();
	const FVector TraceEnd = StartPosition + Direction * TraceMaxDistance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetAvatarActorFromActorInfo());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TraceEnd, ECC_PhysicsBody, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), StartPosition, HitResult.ImpactPoint, FColor::Blue, false, 3.0f,0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 20, FColor::Blue,false, 3.0f);

		FGameplayAbilityTargetData_SingleTargetHit* targetData= new FGameplayAbilityTargetData_SingleTargetHit(HitResult);

		for (TSubclassOf<UGameplayEffect> Effect : AppliedEffects)
		{
			ApplyGameplayEffectToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, targetData, Effect, GetAbilityLevel());
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPosition, TraceEnd, FColor::Red, false, 3.0f,0, 3.0f);
	}
}
