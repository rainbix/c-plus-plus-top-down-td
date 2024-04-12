// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableActor.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

UCLASS()
class SOURCE_API AUnit : public APawn/*, public IDamageableActor*/
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnit();
	
	void ReceiveDamage_Implementation(FDamageInformation DamageInfo);
	bool IsDead_Implementation() const;
	int GetCurrentHealth_Implementation() const;
	int GetMaxHealth_Implementation() const;
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	UHealthComponent* HealthComponent;

	float TimeSinceLastDamage;
};
