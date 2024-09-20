#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SOURCE_API AWeapon : public AActor
{
	GENERATED_BODY()

#pragma region Delegates

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnShot, int, int)
	FOnShot OnShotDelegate;
#pragma endregion
	
public:	
	AWeapon();
	void Fire();
	void Reload() const;
	bool CanShoot() const;
	int GetCurrentAmmo() const;
	int GetSpareAmmo() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class URaycastWeaponShootModule* ShootModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UAmmoModule* AmmoModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShootPointSocket = "ShootSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float FireRate = 1.0f;

	float LastBulletShotTime;
};
