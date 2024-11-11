#include "Projectile.h"

#include "Source.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	RootComponent = ProjectileMeshComponent;
	ProjectileMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ProjectileMeshComponent->SetNotifyRigidBodyCollision(true);
	ProjectileMeshComponent->SetSimulatePhysics(false);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	SetLifeSpan(Range / ProjectileMovementComponent->InitialSpeed);

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	ProjectileMeshComponent->OnComponentHit.RemoveDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::FireInDirection(const FVector& ShootDirection) const
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerActor = GetOwner();
	AActor* InstigatorActor = GetInstigator();


	if (OtherActor && OtherActor != this && OtherComp && OtherActor != GetOwner() && OtherActor != GetInstigator())
	{
		UE_LOG(LogSource, Display, TEXT("Hit actor [%s], Owner: [%s], Instigator: [%s]"), *GetNameSafe(OtherActor), *GetNameSafe(OwnerActor), *GetNameSafe(InstigatorActor))

		if (IAbilitySystemInterface* SourceAbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
		{
			if (UAbilitySystemComponent* AbilitySystemComponent = SourceAbilitySystemInterface->GetAbilitySystemComponent())
			{
				for (FGameplayEffectSpecHandle EffectSpecHandle : EffectsToApply)
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
				}
			}
		}

		Destroy();
	}
}