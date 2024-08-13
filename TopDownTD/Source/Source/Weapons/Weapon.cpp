#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
DEFINE_LOG_CATEGORY_STATIC(LogFWeapon, All, All);
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Fire()
{
	if(!GetWorld()) return;

	double currentTime = GetWorld()->GetTime().GetWorldTimeSeconds();
	if(currentTime - LastBulletShotTime < FireRate)
	{
		return;
	}

	LastBulletShotTime = currentTime;
	UE_LOG(LogFWeapon, Display, TEXT("Fire)"))

	const FTransform ownerTransform = GetOwner()->GetTransform();
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(ShootPointSocket);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = ownerTransform.Rotator().Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_PhysicsBody, CollisionParams);
	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f,0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 20, FColor::Blue,false, 3.0f);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), DamageValue, GetInstigatorController(), this, DamageTypeClass);
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f,0, 3.0f);
	}
}

