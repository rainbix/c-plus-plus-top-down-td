// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Weapon_Fire.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/Weapons/RangedWeapon.h"

UGameplayAbility_Weapon_Fire::UGameplayAbility_Weapon_Fire()
{
	InputId = EAbilityInputID::Fire;
	AbilityTags.AddTag(TAG_WeaponFireType);
}

void UGameplayAbility_Weapon_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	
	UAbilityTask_WaitDelay* WaitDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, FireDelay);
	WaitDelayTask->OnFinish.AddDynamic(this, &ThisClass::OnCompleted);
	WaitDelayTask->ReadyForActivation();

	ARangedWeapon* Weapon = GetWeaponInstance();
	Weapon->UpdateFiringTime();

	OnFire();
}

void UGameplayAbility_Weapon_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UGameplayAbility_Weapon_Fire::OnCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGameplayAbility_Weapon_Fire::OnCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
}

void UGameplayAbility_Weapon_Fire::OnFire()
{
	ARangedWeapon* Weapon = GetWeaponInstance();

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
