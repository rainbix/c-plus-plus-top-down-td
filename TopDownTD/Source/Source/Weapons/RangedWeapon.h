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
	bool CheckShootCost() const;
	void ApplyShootCost() const;
	int GetCurrentAmmo() const;
	int GetSpareAmmo() const;
	EWeaponTypes GetWeaponType() const;
	bool CanReload() const;
	void ApplyReload() const;

	void OnEquip(UAbilitySystemComponent* AbilitySystemComponent);
	void OnUnequip(UAbilitySystemComponent* AbilitySystemComponent);
	FVector GetShootStartPosition() const;
	FVector GetShootDirection() const;
	void UpdateFiringTime();
	float GetTimeSinceLastFire() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TObjectPtr<UAbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", Instanced)
	TObjectPtr<class UInfiniteAmmoModule> AmmoModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category="Weapon")
	EWeaponTypes WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	FName ShootPointSocket = "ShootSocket";

	float LastFireTime;

	UPROPERTY()
	FAbilitySet_GrantedHandles GrantedHandles;
private:
	void HandleAmmoChanged();
};
