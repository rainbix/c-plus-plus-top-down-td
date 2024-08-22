#include "RaycastWeaponShootModule.h"

#include "Kismet/GameplayStatics.h"

URaycastWeaponShootModule::URaycastWeaponShootModule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URaycastWeaponShootModule::Shoot(FVector StartPosition, FVector Direction)
{
	Super::Shoot(StartPosition, Direction);

	const FVector TraceEnd = StartPosition + Direction * TraceMaxDistance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, TraceEnd, ECC_PhysicsBody, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), StartPosition, HitResult.ImpactPoint, FColor::Blue, false, 3.0f,0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 20, FColor::Blue,false, 3.0f);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), DamageValue, GetOwner()->GetInstigatorController(), GetOwner(), DamageTypeClass);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPosition, TraceEnd, FColor::Red, false, 3.0f,0, 3.0f);
	}
}