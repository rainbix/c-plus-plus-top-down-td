#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Source/AbilitySystem/AbilitySet.h"
#include "Source/HUD/EWeaponTypes.h"
#include "RangedWeapon.generated.h"

class UAbilitySet;
class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS()
class SOURCE_API ARangedWeapon : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, ARangedWeapon*)
	FOnAmmoChanged OnAmmoChanged;
	
	ARangedWeapon();
	void Reload() const;
	bool CanShoot() const;
	int GetCurrentAmmo() const;
	int GetSpareAmmo() const;
	EWeaponTypes GetWeaponType() const;

	void OnEquip(UAbilitySystemComponent* AbilitySystemComponent);
	void OnUnequip(UAbilitySystemComponent* AbilitySystemComponent);
	FVector GetShootStartPosition() const;
	FVector GetShootDirection() const;
	void UpdateFiringTime();
	float GetTimeSinceLastFire() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Parameters")
	TObjectPtr<UAbilitySet> AbilitySet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UAmmoModule* AmmoModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category="Parameters")
	EWeaponTypes WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShootPointSocket = "ShootSocket";

	float LastFireTime;

	UPROPERTY()
	FAbilitySet_GrantedHandles GrantedHandles;
private:
	void HandleAmmoChanged();
};
