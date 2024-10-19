// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilitySet.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility_BaseAbility;

USTRUCT()
struct FAbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility_BaseAbility> Ability = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};

USTRUCT()
struct FAbilitySet_GameplayEffects
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> Effect = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	int32 EffectLevel = 1;
};

USTRUCT()
struct FAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(FGameplayAbilitySpecHandle Handle);
	void AddGameplayEffectHandle(FActiveGameplayEffectHandle Handle);
	void TakeFromAbilitySystem(UAbilitySystemComponent* ASC);

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

};

/**
 * 
 */
UCLASS()
class SOURCE_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, FAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const;
protected:

	UPROPERTY(EditDefaultsOnly, Category="GameplayAbilities", meta=(TitleProperty=Ability))
	TArray<FAbilitySet_GameplayAbility> GrantedGameplayAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="GameplayEffects", meta=(TitleProperty=GameplayEffects))
	TArray<FAbilitySet_GameplayEffects> GrantedGameplayEffects;
};
