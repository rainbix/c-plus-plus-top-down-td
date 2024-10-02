// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSet.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SOURCE_API UHealthAttributeSet : public USAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Health")
	FGameplayAttributeData MaxHealth;

public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UHealthAttributeSet();
	
	//~ Helper functions for "Health" attributes
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, CurrentHealth);
	
	//~ Helper functions for "MaxHealth" attributes
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
};
