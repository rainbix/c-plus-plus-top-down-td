#include "TowerActor.h"
#include "SourceCharacter.h"  // Включіть файл заголовка вашого гравця
#include "SourceGameplayTags.h"
#include "AbilitySystem/AbilitySet.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ATowerActor::ATowerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Range = 1000.0f;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TowerMesh"));
	RootComponent = MeshComponent;
	
	AbilitySystemComponent = CreateDefaultSubobject<USourceAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySet = nullptr;
}

void ATowerActor::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	SetInstigator(OwnerCharacter);

	GetWorldTimerManager().SetTimer(SearchTargetTimerHandle, this, &ATowerActor::FindTarget, TargetSearchDelay, true);
	
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, this);
	}
}

void ATowerActor::FindTarget()
{
	float DistanceSqr;
	if (IsValidTarget(TargetCharacter, DistanceSqr))
	{
		return;
	}
	
	TArray<FOverlapResult> OverlapTargets;
	FCollisionShape Shape = FCollisionShape::MakeSphere(Range);
	FCollisionQueryParams Params;
	Params.bDebugQuery = true;

	FCollisionObjectQueryParams ObjectQueryParams(ECC_Pawn);
	GetWorld()->OverlapMultiByObjectType(OverlapTargets, GetActorLocation(), GetActorQuat(), ObjectQueryParams, Shape, Params);

	ACharacter* ClosestTarget = nullptr;
	float ClosestDistanceSqr = FLT_MAX;

	for (FOverlapResult Result : OverlapTargets)
	{
		if (ACharacter* Character = Cast<ACharacter>(Result.GetActor()))
		{
			if (!IsValidTarget(Character, DistanceSqr))
			{
				continue;
			}

			if (DistanceSqr < ClosestDistanceSqr)
			{
				ClosestDistanceSqr = DistanceSqr;
				ClosestTarget = Character;
			}
		}
	}

	TargetCharacter = ClosestTarget;
}

bool ATowerActor::IsValidTarget(const ACharacter* Character, float& DistanceSqr) const
{
	if (!Character)
	{
		return false;
	}

	if (Character == GetInstigator())
	{
		return false;
	}

	DistanceSqr = (Character->GetActorLocation() - GetActorLocation()).SquaredLength();

	if (DistanceSqr > Range * Range)
	{
		return false;
	}
	
	if (UHealthComponent* HealthComponent = Character->FindComponentByClass<UHealthComponent>())
	{
		if (HealthComponent->IsDead())
		{
			return false;
		}
	}

	return true;
}

void ATowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceSquared;
	
	if (!IsValidTarget(TargetCharacter, DistanceSquared))
	{
		if (HadTarget)
		{
			HadTarget = false;
			AbilitySystemComponent->RemoveLooseGameplayTag(TAG_Input_Fire);
		}
		return;
	}

	if (!HadTarget)
	{
		HadTarget = true;
		AbilitySystemComponent->AddLooseGameplayTag(TAG_Input_Fire);
	}

	FVector Direction = TargetCharacter->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	FRotator LookAtRotation = Direction.Rotation();
	LookAtRotation.Pitch = 0;
	SetActorRotation(LookAtRotation);
}


AActor* ATowerActor::GetTarget() const
{
	return TargetCharacter;
}
