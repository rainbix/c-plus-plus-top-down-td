// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ARangedWeapon;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();
	void Reload();
	ARangedWeapon* GetCurrentWeapon() const;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, const ARangedWeapon* newWeapon)
	FOnWeaponChanged OnWeaponChanged;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, const ARangedWeapon* weapon)
	FOnWeaponChanged OnWeaponAmmoChange;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TSubclassOf<ARangedWeapon> DefaultWeaponClass;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponSocketName = "WeaponSocket";
	
private:
	UPROPERTY()
	ARangedWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystem;
	void SpawnWeapon();

	void SubscribeOnWeapon();
	void UnsubscribeOnWeapon();
	void HandleWeaponAmmoChanged(ARangedWeapon* weapon) const;
};
