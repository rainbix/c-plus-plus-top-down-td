﻿#include "ClipAmmoModule.h"
#include "Source/Source.h"

void UClipAmmoModule::Initialize()
{
	Super::Initialize();

	CurrentClipAmmo = MaxClipAmmo;
	SpareAmmoLeft = MaxSpareAmmo;
}

bool UClipAmmoModule::CheckShootCost() const
{
	return CurrentClipAmmo >= AmmoPerShot;
}

void UClipAmmoModule::ApplyShootCost()
{
	Super::ApplyShootCost();

	CurrentClipAmmo -= AmmoPerShot;
	OnAmmoChanged.Execute();
}

void UClipAmmoModule::AddAmmo(int Value)
{
	SpareAmmoLeft = FMath::Clamp(SpareAmmoLeft + Value, 0, MaxSpareAmmo);
	UE_LOG(LogFWeapon, Display, TEXT("Add ammo: SpareAmmoLeft [%i])"), SpareAmmoLeft)
	OnAmmoChanged.Execute();
}

int UClipAmmoModule::GetCurrentAmmo() const
{
	return CurrentClipAmmo;
}

int UClipAmmoModule::GetSpareAmmo() const
{
	return SpareAmmoLeft;
}

bool UClipAmmoModule::CanReload() const
{
	return CurrentClipAmmo < MaxClipAmmo && SpareAmmoLeft > 0;
}

void UClipAmmoModule::ApplyReload()
{
	int MissingAmmo = MaxClipAmmo - CurrentClipAmmo;
	int AmmoToLoad = FMath::Min(MissingAmmo, SpareAmmoLeft);

	CurrentClipAmmo += AmmoToLoad;
	SpareAmmoLeft -= AmmoToLoad;
	OnAmmoChanged.Execute();
}
