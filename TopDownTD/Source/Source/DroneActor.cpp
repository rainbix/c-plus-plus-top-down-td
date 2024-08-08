#include "DroneActor.h"
#include "SourceCharacter.h"
#include "Kismet/GameplayStatics.h"

ACharacter* MainCharacter;

ADroneActor::ADroneActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementSpeed = 500.0f;
	AcceptanceRadius = 150.0f;
}

void ADroneActor::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ADroneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainCharacter)
	{
		FVector targetPosition = MainCharacter->GetActorLocation();
		FVector currentPosition = GetActorLocation(); 

		FVector direction = targetPosition - currentPosition;
		direction.Normalize();

		FVector newPosition = currentPosition + direction * MovementSpeed * DeltaTime;

		if (FVector::Distance(targetPosition, newPosition) < AcceptanceRadius)
		{
			// float deltaHeight = 50.0f * FMath::Sin(GetGameTimeSinceCreation());
			// newPosition = currentPosition + FVector(0.0f, deltaHeight, 0.0f);
			//
			// AddActorLocalOffset(newPosition);
		}
		else
		{
			SetActorLocation(newPosition);
		}
	}
}
