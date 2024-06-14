#pragma once

UENUM()
enum class EWeaponTypes : uint8
{
	None,
	Weapon1,
	Weapon2,
	Weapon3
};

struct FWeaponData
{
	int maxAmmo;
	int curAmmo;
	EWeaponTypes weaponType;

	FWeaponData(int MaxAmmo, int CurAmmo, EWeaponTypes WeaponType)
		: maxAmmo(MaxAmmo),	curAmmo(CurAmmo), weaponType(WeaponType)
	{ }
};
