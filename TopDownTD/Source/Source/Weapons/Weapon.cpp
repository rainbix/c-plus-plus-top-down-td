#include "Weapon.h"
#include "AmmoModule/ClipAmmoModule.h"
#include "ShootModule/RaycastWeaponShootModule.h"
#include "Components/SkeletalMeshComponent.h"
#include "Source/Source.h"

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
	
	OnShotDelegate.Broadcast(GetCurrentAmmo(), GetSpareAmmo());
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

int AWeapon::GetCurrentAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetCurrentAmmo();
}

int AWeapon::GetSpareAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetSpareAmmo();
}

