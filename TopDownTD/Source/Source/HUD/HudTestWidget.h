// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EWeaponTypes.h"
#include "Blueprint/UserWidget.h"
#include "HudTestWidget.generated.h"

struct FWeaponData;

UCLASS()
class SOURCE_API UHudTestWidget : public UUserWidget
{
public:
	#pragma region Delegates
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthInitialize, int)
	FOnHealthInitialize OnHealthInitializeDelegate;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthIncreased, int)
	FOnHealthIncreased OnHealthIncreasedDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthDecreased, int)
	FOnHealthIncreased OnHealthDecreasedDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnShoot, const FWeaponData*)
	FOnShoot OnShootDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnReload, const FWeaponData*)
	FOnReload OnReloadDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChange, const FWeaponData*)
	FOnWeaponChange OnWeaponChangeDelegate;

	#pragma endregion

	#pragma region Functions
	
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(int amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseHealth(int amount);

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void NextWeapon();

	UFUNCTION(BlueprintCallable)
	void PreviousWeapon();

	FWeaponData* GetActiveWeaponData();
	
	#pragma endregion 

	#pragma region Properties

	//Health
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int CurHealth = 75;

	//Primary Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Primary")
	int PrimaryStartAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Primary")
	int PrimaryMaxAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Primary")
	EWeaponTypes PrimaryWeaponType;

	//Secondary Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Secondary")
	int SecondaryStartAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Secondary")
	int SecondaryMaxAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Secondary")
	EWeaponTypes SecondaryWeaponType;

	//LastStand Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|LastStand")
	int LastStandStartAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|LastStand")
	int LastStandMaxAmmo = 75;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|LastStand")
	EWeaponTypes LastStandWeaponType;
	
	#pragma endregion 
	
protected:
	virtual void NativeConstruct() override;

private:
	GENERATED_BODY()

	int activeWeaponIndex;
	TArray<FWeaponData*> weaponData;
};
