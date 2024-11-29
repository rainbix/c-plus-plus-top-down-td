#include "Projectile.h"

#include "PlayerCharacterSource.h"
#include "Source.h"
#include "TeamSubsystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

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
	ProjectileMeshComponent->SetGenerateOverlapEvents(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	ProjectileMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	SetLifeSpan(Range / ProjectileMovementComponent->InitialSpeed);

	if (ITeamProvider* InstigatorTeamProvide = Cast<ITeamProvider>(GetInstigator()))
	{
		TeamType = InstigatorTeamProvide->GetTeamType();
	}
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ProjectileMeshComponent->OnComponentHit.RemoveDynamic(this, &AProjectile::OnHit);
	ProjectileMeshComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AProjectile::OnBeginOverlap);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, signed int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	AActor* OwnerActor = GetOwner();
	AActor* InstigatorActor = GetInstigator();

	if (OtherActor && OtherActor != this && OtherActor && OtherActor != GetOwner() && OtherActor != InstigatorActor && !UTeamSubsystem::IsSameTeam(OtherActor, OwnerActor))
	{
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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherActor)
	{
		Destroy();
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
