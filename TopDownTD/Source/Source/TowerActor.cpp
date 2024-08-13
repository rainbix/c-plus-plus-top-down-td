#include "TowerActor.h"
#include "SourceCharacter.h"  // Включіть файл заголовка вашого гравця
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"

ATowerActor::ATowerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 1.0f;
	Range = 1000.0f;
}

void ATowerActor::BeginPlay()
{
	Super::BeginPlay();
    
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerActor::Fire, 1.0f / FireRate, true);

	MainCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ATowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainCharacter)
	{
		FRotator LookAtRotation = (MainCharacter->GetActorLocation() - GetActorLocation()).Rotation();
		SetActorRotation(LookAtRotation);
	}
}

void ATowerActor::Fire()
{
	if (MainCharacter && ProjectileClass)
	{
		FVector MuzzleLocation = GetActorLocation(); 
		FRotator MuzzleRotation = (MainCharacter->GetActorLocation() - MuzzleLocation).Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	}
}