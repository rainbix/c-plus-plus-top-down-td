// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInformation.h"
#include "DamageableActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDamageableActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IDamageableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReceiveDamage(FDamageInformation DamageInfo);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetCurrentHealth();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetMaxHealth();

	virtual void DoShit() abstract;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Something();
};
