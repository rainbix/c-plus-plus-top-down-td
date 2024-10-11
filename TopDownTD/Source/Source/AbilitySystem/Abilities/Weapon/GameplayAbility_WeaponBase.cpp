// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_WeaponBase.h"
#include "Source/Weapons/Weapon.h"
#include "Source/Source.h"

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

AWeapon* UGameplayAbility_WeaponBase::GetWeaponInstance() const
{
	if (FGameplayAbilitySpec* Spec =  GetCurrentAbilitySpec())
	{
		return Cast<AWeapon>(Spec->SourceObject.Get());
	}

	return nullptr;
}