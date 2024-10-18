// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_WeaponBase.h"
#include "Source/Weapons/RangedWeapon.h"
#include "Source/Source.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponReloadType, "Ability.Type.Reload");
UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponFireType, "Ability.Type.Fire");

bool UGameplayAbility_WeaponBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                        const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	if (bResult)
	{
		if(GetWeaponInstance() == nullptr)
		{
			UE_LOG(LogFWeapon, Error, TEXT("Ability [%s] cannot be activated because doesn't have associated weapon with it."), *GetPathName());
			bResult = false;	
		}
	}

	return bResult;
}

ARangedWeapon* UGameplayAbility_WeaponBase::GetWeaponInstance() const
{
	if (FGameplayAbilitySpec* Spec =  GetCurrentAbilitySpec())
	{
		return Cast<ARangedWeapon>(Spec->SourceObject.Get());
	}

	return nullptr;
}