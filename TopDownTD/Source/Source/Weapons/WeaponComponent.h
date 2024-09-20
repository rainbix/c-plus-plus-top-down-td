// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();
	void Fire();
	void Reload();
	AWeapon* GetCurrentWeapon() const;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, const AWeapon* newWeapon)
	FOnWeaponChanged OnWeaponChanged;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, const AWeapon* weapon)
	FOnWeaponChanged OnWeaponAmmoChange;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponSocketName = "WeaponSocket";
	
private:
	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();

	void SubscribeOnWeapon();
	void UnsubscribeOnWeapon();
	void HandleWeaponAmmoChanged(AWeapon* weapon) const;
};
