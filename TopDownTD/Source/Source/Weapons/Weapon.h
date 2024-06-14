// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SOURCE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	//Ammo
	UPROPERTY(EditAnywhere, Category="Gun")
	int MaxAmmo;
	int CurrentAmmo;

	UPROPERTY(EditAnywhere, Category="Gun")
	int MaxClipSize;
	int CurrentClipAmmo;

	UPROPERTY(EditAnywhere, Category="Gun")
	bool AutoReload = true;
	
	bool IsReloading;
	float TimeSinceReloadStart;

	//Shooting
	UPROPERTY(EditAnywhere, Category="Gun")
	float FireRate;
	float LastShotTime;
	bool IsShooting;

	//Logic when shot is dealt (raycast, spawn projectile, etc)
	void OnShot();

public:	
	virtual void OnEquip();
	virtual void OnUnequip();
	//Called when received input
	virtual void Shoot();
	virtual void Reload();
	virtual bool HasAmmo();
};
