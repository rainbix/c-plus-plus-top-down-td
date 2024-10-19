// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySet.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility_BaseAbility.h"
#include "Source/Source.h"

void FAbilitySet_GrantedHandles::AddAbilitySpecHandle(FGameplayAbilitySpecHandle Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::AddGameplayEffectHandle(FActiveGameplayEffectHandle Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::TakeFromAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	for (const FGameplayAbilitySpecHandle Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			ASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
}

void UAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* ASC, FAbilitySet_GrantedHandles* OutGrantedHandles,
                                      UObject* SourceObject) const
{
	check(ASC);

	//GiveAbilities
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogSourceAbilitySystem, Error, TEXT("GrantedGameplayAbilities [%d] on ability set [%s] is not valid"), AbilityIndex, *GetNameSafe(this))
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.Ability, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	//Give GameplayEffects
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
	{
		const FAbilitySet_GameplayEffects& EffectToGrant = GrantedGameplayEffects[EffectIndex];

		if (!IsValid(EffectToGrant.Effect))
		{
			UE_LOG(LogSourceAbilitySystem, Error, TEXT("GrantedGameplayEffects [%d] on ability set [%s] is not valid"), EffectIndex, *GetNameSafe(this))
			continue;
		}
		UGameplayEffect* Effect = EffectToGrant.Effect->GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle EffectHandle = ASC->ApplyGameplayEffectToSelf(Effect, EffectToGrant.EffectLevel, ASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(EffectHandle);
		}
	}
}
