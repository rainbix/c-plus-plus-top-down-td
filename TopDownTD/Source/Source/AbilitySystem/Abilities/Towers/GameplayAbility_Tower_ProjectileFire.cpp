// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Tower_ProjectileFire.h"

#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/Projectile.h"
#include "Source/SourceGameplayTags.h"
#include "Source/TowerActor.h"

UGameplayAbility_Tower_ProjectileFire::UGameplayAbility_Tower_ProjectileFire()
{
	FireRate = 1.0f;
	ProjectileClass = nullptr;

	AbilityTags.AddTag(TAG_WeaponFireType);
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = TAG_Input_Fire;
	AbilityTriggers.Add(TriggerData);
}

void UGameplayAbility_Tower_ProjectileFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Fire();
}

void UGameplayAbility_Tower_ProjectileFire::OnDelayCompleted()
{
	Fire();
}

void UGameplayAbility_Tower_ProjectileFire::Fire()
{
	ATowerActor* Tower = GetTowerInstance();
	const AActor* Target = Tower->GetTarget();

	if (!Target)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, true);
	}

	const FVector MuzzleLocation = Tower->GetSkeletalMesh()->GetSocketLocation(ShootPointSocketName);
	FVector Direction = Target->GetActorLocation() - MuzzleLocation;
	Direction.Normalize();
	FRotator MuzzleRotation = Direction.Rotation();
	MuzzleRotation.Pitch = 0;

	const FTransform ProjectileTransform(MuzzleRotation, MuzzleLocation);
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, Tower, Tower->GetInstigator(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	for (const TSubclassOf<UGameplayEffect> Effect : EffectsToApply)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(Effect, GetAbilityLevel());
		Projectile->EffectsToApply.Add(EffectSpecHandle);
		Projectile->Range = Tower->GetRange();
	}

	Projectile->FinishSpawning(ProjectileTransform);
	
	UAbilityTask_WaitDelay* AbilityTask = UAbilityTask_WaitDelay::WaitDelay(this, FireRate);
	AbilityTask->OnFinish.AddDynamic(this, &ThisClass::OnDelayCompleted);
	AbilityTask->ReadyForActivation();
}
