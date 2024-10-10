#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Actor.h"
#include "Source/HUD/EWeaponTypes.h"
#include "Weapon.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;

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

	void OnEquip(UAbilitySystemComponent* AbilitySystemComponent);
	void OnUnequip(UAbilitySystemComponent* AbilitySystemComponent);
	FVector GetShootStartPosition() const;
	FVector GetShootDirection();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TSubclassOf<UGameplayAbility> FireAbility;

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

	UPROPERTY()
	FGameplayAbilitySpecHandle FireAbilitySpec;

	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystem;
private:
	void HandleAmmoChanged();
};
