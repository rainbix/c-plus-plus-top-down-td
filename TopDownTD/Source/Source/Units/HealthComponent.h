// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),
	Blueprintable)
class SOURCE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UHealthComponent();

	virtual bool IsDead();
	virtual int GetCurrentHealth();
	virtual int GetMaxHealth();

protected:

	UPROPERTY(EditAnywhere, Category="Health")
	int MaxHealth;

	int CurrentHealth;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnDeath();
	UFUNCTION()
	virtual void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
