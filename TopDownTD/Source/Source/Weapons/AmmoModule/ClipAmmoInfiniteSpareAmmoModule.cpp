// Fill out your copyright notice in the Description page of Project Settings.


#include "ClipAmmoInfiniteSpareAmmoModule.h"

void UClipAmmoInfiniteSpareAmmoModule::Initialize()
{
	Super::Initialize();

	CurrentClipAmmo = MaxClipAmmo;
}

bool UClipAmmoInfiniteSpareAmmoModule::CheckShootCost() const
{
	return CurrentClipAmmo > 0;
}

void UClipAmmoInfiniteSpareAmmoModule::ApplyShootCost()
{
	CurrentClipAmmo--;

	OnAmmoChanged.Execute();
}

int UClipAmmoInfiniteSpareAmmoModule::GetCurrentAmmo() const
{
	return CurrentClipAmmo;
}

int UClipAmmoInfiniteSpareAmmoModule::GetSpareAmmo() const
{
	return MaxClipAmmo;
}

bool UClipAmmoInfiniteSpareAmmoModule::CanReload() const
{
	return CurrentClipAmmo < MaxClipAmmo;
}

void UClipAmmoInfiniteSpareAmmoModule::ApplyReload()
{
	CurrentClipAmmo = MaxClipAmmo;

	OnAmmoChanged.Execute();
}



