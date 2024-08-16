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
	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UWeaponShootModule* ShootModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShootPointSocket = "ShootSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float FireRate = 1.0f;

	float LastBulletShotTime;
};
