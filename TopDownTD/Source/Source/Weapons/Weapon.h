#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Source/AbilitySystem/AbilitySet.h"
#include "Source/HUD/EWeaponTypes.h"
#include "Weapon.generated.h"

class UAbilitySet;
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

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySet> AbilitySet;

	UPROPERTY()
	FAbilitySet_GrantedHandles GrantedHandles;
private:
	void HandleAmmoChanged();
};
