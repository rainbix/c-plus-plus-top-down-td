// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Source/AbilitySystem/EAbilityInputID.h"
#include "GameplayAbility_BaseAbility.generated.h"

class UAbilityCost;
/**
 * 
 */
UCLASS(Abstract)
class SOURCE_API UGameplayAbility_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_BaseAbility();
	int32 GetInputId();

protected:
	UPROPERTY(EditAnywhere)
	EAbilityInputID InputId;
	
	// Additional costs that must be paid to activate this ability
	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UAbilityCost>> AdditionalCosts;
	
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

};
