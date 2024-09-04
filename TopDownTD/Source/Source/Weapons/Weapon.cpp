﻿#include "Weapon.h"

#include "AmmoModule/ClipAmmoModule.h"
#include "ShootModule/RaycastWeaponShootModule.h"
#include "ShootModule/WeaponShootModule.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFWeapon, All, All);

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	ShootModule = CreateDefaultSubobject<URaycastWeaponShootModule>("WeaponShootModule");
	AmmoModule = CreateDefaultSubobject<UClipAmmoModule>("AmmoModule");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Fire()
{
	if(!ShootModule) return;
	if(!GetWorld()) return;
	if(!CanShoot()) return;

	double currentTime = GetWorld()->GetTime().GetWorldTimeSeconds();
	if (currentTime - LastBulletShotTime < FireRate)
	{
		return;
	}

	LastBulletShotTime = currentTime;
	UE_LOG(LogFWeapon, Display, TEXT("Fire)"))

	const FTransform ownerTransform = GetOwner()->GetTransform();
	const FTransform socketTransform = WeaponMesh->GetSocketTransform(ShootPointSocket);
	const FVector startPosition = socketTransform.GetLocation();
	const FVector shootDirection = ownerTransform.Rotator().Vector();

	ShootModule->Shoot(startPosition, shootDirection);

	if (AmmoModule)
	{
		AmmoModule->OnShot();
	}
}

void AWeapon::Reload() const
{
	if(!AmmoModule) return;

	AmmoModule->Reload();
}

bool AWeapon::CanShoot() const
{
	if (!AmmoModule) return true;
	
	return AmmoModule->CanShoot();
}
