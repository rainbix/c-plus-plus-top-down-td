// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbility_Weapon_Reload.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Source/Weapons/RangedWeapon.h"
#include "NativeGameplayTags.h"
#include "Source/SourceGameplayTags.h"

UGameplayAbility_Weapon_Reload::UGameplayAbility_Weapon_Reload()
{
	AbilityTags.AddTag(TAG_WeaponReloadType);
	BlockAbilitiesWithTag.AddTag(TAG_WeaponFireType);
	ActivationOwnedTags.AddTag(TAG_WeaponReloadEvent);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = TAG_Input_Reload;
	AbilityTriggers.Add(TriggerData);
}

bool UGameplayAbility_Weapon_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ARangedWeapon* Weapon = GetWeaponInstance();

	return Weapon->CanReload();
}

void UGameplayAbility_Weapon_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_WaitDelay* WaitDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, ReloadTime);
	WaitDelayTask->OnFinish.AddDynamic(this, &ThisClass::OnCompleted);
	WaitDelayTask->ReadyForActivation();

	//Temporary text
	GEngine->AddOnScreenDebugMessage(1001, ReloadTime, FColor::Yellow, TEXT("Reloading!"));	
}

void UGameplayAbility_Weapon_Reload::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bWasCancelled)
	{
		const ARangedWeapon* Weapon = GetWeaponInstance();
		Weapon->ApplyReload();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GEngine->RemoveOnScreenDebugMessage(1001);	
}

void UGameplayAbility_Weapon_Reload::OnCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGameplayAbility_Weapon_Reload::OnCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
}