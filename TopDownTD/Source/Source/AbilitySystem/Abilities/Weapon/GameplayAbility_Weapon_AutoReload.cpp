// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbility_Weapon_AutoReload.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/SourceGameplayTags.h"
#include "Source/Weapons/RangedWeapon.h"

UGameplayAbility_Weapon_AutoReload::UGameplayAbility_Weapon_AutoReload()
{
	ActivationPolicy = EAbilityActivationPolicy::OnSpawn;
}

void UGameplayAbility_Weapon_AutoReload::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PeriodicCheck();
}

void UGameplayAbility_Weapon_AutoReload::PeriodicCheck()
{
	UAbilityTask_WaitDelay* AbilityTask = UAbilityTask_WaitDelay::WaitDelay(this, CheckInterval);
	AbilityTask->OnFinish.AddDynamic(this, &ThisClass::CheckReloadRequired);
	AbilityTask->ReadyForActivation();
}

void UGameplayAbility_Weapon_AutoReload::CheckReloadRequired()
{
	if (const ARangedWeapon* Weapon = GetWeaponInstance())
	{
		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
		bool IsReloading = ASC->HasMatchingGameplayTag(TAG_WeaponReloadEvent);
		
		if (!IsReloading && Weapon->CanReload() && !Weapon->CheckShootCost())
		{
			FGameplayEventData Payload;
			Payload.EventTag = TAG_Input_Reload;
			SendGameplayEvent(TAG_Input_Reload, Payload);
		}
	}
	
	PeriodicCheck();
}
