// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbility_Tower_Base.h"
#include "Source/Source.h"
#include "Source/TowerActor.h"

bool UGameplayAbility_Tower_Base::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                                     const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	if (bResult)
	{
		if (GetTowerInstance() == nullptr)
		{
			UE_LOG(LogSource, Error, TEXT("Ability [%s] cannot be activated because doesn't have associated tower with it."), *GetPathName());
			bResult = false;	
		}
	}

	return bResult;
}

ATowerActor* UGameplayAbility_Tower_Base::GetTowerInstance() const
{
	if (FGameplayAbilitySpec* Spec =  GetCurrentAbilitySpec())
	{
		return Cast<ATowerActor>(Spec->SourceObject.Get());
	}

	return nullptr;
}