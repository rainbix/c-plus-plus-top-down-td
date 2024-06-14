#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	MaxAmmo = 10;
	FireRate = 1;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	LastShotTime = FLT_MAX;
}


void AWeapon::OnShot()
{
	//todo:linecast here
	UE_LOG(LogTemp, Error, TEXT("ShootStarted"), *GetNameSafe(this));
}

void AWeapon::OnEquip()
{
}

void AWeapon::OnUnequip()
{
	IsReloading = false;
	IsShooting = false;
}

void AWeapon::Shoot()
{
	IsShooting = true;

	float currentTime = UGameplayStatics::GetTimeSeconds(GetWorld());
	if (currentTime - LastShotTime < FireRate)
	{
		return;
	}

	LastShotTime = currentTime;
	OnShot();
}

void AWeapon::Reload()
{
	if (!IsReloading)
	{
		IsReloading = true;
		TimeSinceReloadStart = 0;
	}
}

bool AWeapon::HasAmmo()
{
	return CurrentClipAmmo > 0;
}
