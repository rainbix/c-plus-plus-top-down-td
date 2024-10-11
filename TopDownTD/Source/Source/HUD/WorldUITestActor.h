// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldUITestActor.generated.h"

UCLASS()
class SOURCE_API AWorldUITestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldUITestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="HealthBar")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category="HealthBar")
	float Damage;

	UFUNCTION(BlueprintCallable)
	void ApplyCustomDamage();
};
