// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Source/AbilitySystem/EAbilityInputID.h"
#include "GameplayAbility_BaseAbility.generated.h"

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
};
