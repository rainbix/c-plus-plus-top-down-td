// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Weapon_Fire.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/SourceGameplayTags.h"
#include "Source/TeamSubsystem.h"
#include "Source/Physics/SourceCollisionChannels.h"
#include "Source/Weapons/RangedWeapon.h"

UGameplayAbility_Weapon_Fire::UGameplayAbility_Weapon_Fire()
{
	AbilityTags.AddTag(TAG_WeaponFireType);
	ActivationOwnedTags.AddTag(TAG_WeaponFireEvent);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = TAG_Input_Fire;
	AbilityTriggers.Add(TriggerData);
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

	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByChannel(HitResults, StartPosition, TraceEnd, Source_ObjectType_Bullet, CollisionParams);

	FHitResult ClosestHit;
	
	for (int i = 0; i < HitResults.Num(); i++)
	{
		FHitResult HitResult = HitResults[i];
		
		APawn* HitPawn = Cast<APawn>(HitResult.GetActor());
		
		if (HitPawn && UTeamSubsystem::IsSameTeam(HitPawn, Weapon))
		{
			continue;
		}
		
		ClosestHit = HitResult;
		break;
	}
	
	if (ClosestHit.GetActor())
	{
		DrawDebugLine(GetWorld(), StartPosition, ClosestHit.ImpactPoint, FColor::Blue, false, 3.0f,0, 3.0f);
		DrawDebugSphere(GetWorld(), ClosestHit.ImpactPoint, 7.0f, 20, FColor::Blue,false, 3.0f);

		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(ClosestHit);

		for (TSubclassOf<UGameplayEffect> Effect : AppliedEffects)
		{
			ApplyGameplayEffectToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TargetData, Effect, GetAbilityLevel());
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPosition, TraceEnd, FColor::Red, false, 3.0f,0, 3.0f);
	}
}
