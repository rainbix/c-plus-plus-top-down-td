// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageInformation.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),
	Blueprintable)
class SOURCE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void ReceiveDamage(FDamageInformation& DamageInfo);
	virtual bool IsDead();
	virtual int GetCurrentHealth();
	virtual int GetMaxHealth();

protected:

	UPROPERTY(EditAnywhere, Category="Health")
	int MaxHealth;

	int CurrentHealth;
	
	// Called when the game starts
	virtual void BeginPlay() override;
};
