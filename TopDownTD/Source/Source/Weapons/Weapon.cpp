#include "Weapon.h"

#include "RaycastWeaponShootModule.h"
#include "WeaponShootModule.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFWeapon, All, All);

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	ShootModule = CreateDefaultSubobject<URaycastWeaponShootModule>("WeaponShootModule");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Fire()
{
	if(!ShootModule) return;
	if(!GetWorld()) return;

	double currentTime = GetWorld()->GetTime().GetWorldTimeSeconds();
	if(currentTime - LastBulletShotTime < FireRate)
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
}

