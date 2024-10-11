#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Source/HUD/EWeaponTypes.h"
#include "Weapon.generated.h"

UCLASS()
class SOURCE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, AWeapon*)
	FOnAmmoChanged OnAmmoChanged;
	
	AWeapon();
	void Fire();
	void Reload() const;
	bool CanShoot() const;
	int GetCurrentAmmo() const;
	int GetSpareAmmo() const;
	EWeaponTypes GetWeaponType() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class URaycastWeaponShootModule* ShootModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UAmmoModule* AmmoModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category="Parameters")
	EWeaponTypes WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShootPointSocket = "ShootSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float FireRate = 1.0f;

	float LastBulletShotTime;

private:
	void HandleAmmoChanged();
};
