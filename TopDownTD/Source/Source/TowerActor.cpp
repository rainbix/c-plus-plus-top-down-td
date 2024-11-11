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

	MainCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	SetInstigator(MainCharacter);

	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, this);
	}
}

void ATowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainCharacter)
	{
		FVector Direction = MainCharacter->GetActorLocation() - GetActorLocation();
		float Distance = Direction.Length();
		FVector DirectionNormalized = Direction / Distance;

		if (Distance > Range)
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

		
		FRotator LookAtRotation = DirectionNormalized.Rotation();
		LookAtRotation.Pitch = 0;
		SetActorRotation(LookAtRotation);
	}
}


AActor* ATowerActor::GetTarget() const
{
	return MainCharacter;
}
