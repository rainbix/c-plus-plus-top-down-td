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
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->Velocity = FVector::ForwardVector;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	RootComponent = ProjectileMeshComponent;
	ProjectileMeshComponent->SetNotifyRigidBodyCollision(true);
	ProjectileMeshComponent->SetSimulatePhysics(false);
	ProjectileMeshComponent->SetCollisionProfileName(TEXT("Bullet"));
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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerActor = GetOwner();
	AActor* InstigatorActor = GetInstigator();

	if (OtherActor && OtherActor != this && OtherComp && OtherActor != GetOwner() && OtherActor != GetInstigator())
	{
		UE_LOG(LogSource, Display, TEXT("Hit actor [%s], Hit Component: [%s] Owner: [%s], Instigator: [%s]"), *GetNameSafe(OtherActor), *GetNameSafe(OtherComp), *GetNameSafe(OwnerActor), *GetNameSafe(InstigatorActor))

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