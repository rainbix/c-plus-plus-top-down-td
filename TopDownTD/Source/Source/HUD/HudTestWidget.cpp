// Fill out your copyright notice in the Description page of Project Settings.


#include "HudTestWidget.h"
#include "FWeaponData.h"

void UHudTestWidget::IncreaseHealth(int amount)
{
	CurHealth = FMath::Clamp(CurHealth + amount, 0, MaxHealth);
	OnHealthIncreasedDelegate.Broadcast(CurHealth);
}

void UHudTestWidget::DecreaseHealth(int amount)
{
	CurHealth = FMath::Clamp(CurHealth - amount, 0, MaxHealth);
	OnHealthDecreasedDelegate.Broadcast(CurHealth);
}


void UHudTestWidget::Shoot()
{
	GetActiveWeaponData()->curAmmo = FMath::Clamp(GetActiveWeaponData()->curAmmo - 1, 0, GetActiveWeaponData()->maxAmmo);
	OnShootDelegate.Broadcast(GetActiveWeaponData());
}

void UHudTestWidget::Reload()
{
	GetActiveWeaponData()->curAmmo = GetActiveWeaponData()->maxAmmo;
	OnReloadDelegate.Broadcast(GetActiveWeaponData());
}

void UHudTestWidget::NextWeapon()
{
	activeWeaponIndex++;
	
	if (activeWeaponIndex >= weaponData.Num())
		activeWeaponIndex = 0;

	OnWeaponChangeDelegate.Broadcast(GetActiveWeaponData());
}

void UHudTestWidget::PreviousWeapon()
{
	activeWeaponIndex--;
	
	if (activeWeaponIndex < 0)
		activeWeaponIndex = weaponData.Num() - 1;
		
	OnWeaponChangeDelegate.Broadcast(GetActiveWeaponData());
}

void UHudTestWidget::Pause()
{
	OnPauseDelegate.Broadcast();
}

void UHudTestWidget::Build()
{
	OnBuildDelegate.Broadcast();
}

void UHudTestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	weaponData.Reserve(3);
	weaponData.Emplace(new FWeaponData(PrimaryMaxAmmo, PrimaryStartAmmo, PrimaryWeaponType));
	weaponData.Emplace(new FWeaponData(SecondaryMaxAmmo, SecondaryStartAmmo, SecondaryWeaponType));
	weaponData.Emplace(new FWeaponData(LastStandMaxAmmo, LastStandStartAmmo, LastStandWeaponType));
	
	activeWeaponIndex = 0;
}

FWeaponData* UHudTestWidget::GetActiveWeaponData()
{
	return weaponData[activeWeaponIndex];
}
