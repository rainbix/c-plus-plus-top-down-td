#pragma once

#include "EWeaponTypes.h"

struct FWeaponData
{
	int maxAmmo;
	int curAmmo;
	EWeaponTypes weaponType;

	FWeaponData(int MaxAmmo, int CurAmmo, EWeaponTypes WeaponType)
		: maxAmmo(MaxAmmo),	curAmmo(CurAmmo), weaponType(WeaponType)
	{ }
};
