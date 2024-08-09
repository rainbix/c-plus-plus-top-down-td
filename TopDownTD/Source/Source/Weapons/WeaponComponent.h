// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();
	void Fire();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TSubclassOf<class AWeapon> DefaultWeaponClass;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponSocketName = "WeaponSocket";
	
private:
	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
};
