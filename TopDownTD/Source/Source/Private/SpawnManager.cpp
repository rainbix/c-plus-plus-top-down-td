// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnManager.h"
#include "PlayerCharacterSource.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_currentSpawnInterval = 5;
	maxSpawnCount = 5;
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_currentSpawnInterval += DeltaTime;

	if (m_currentSpawnInterval >= spawnInterval && m_spawnedEnemies.Num() < maxSpawnCount)
	{
		m_currentSpawnInterval = 0;

		FVector location = GetActorLocation();

		if (!locationRandomRange.IsNearlyZero())
		{
			location.X += FMath::RandRange(-locationRandomRange.X, locationRandomRange.X);
			location.Y += FMath::RandRange(-locationRandomRange.Y, locationRandomRange.Y);
		}

		FRotator rotator = FRotator::ZeroRotator;
		FActorSpawnParameters spawnInfo;
		
		APlayerCharacterSource* character =
			GetWorld()->SpawnActor<APlayerCharacterSource>(characterPrefab, location, rotator, spawnInfo);

		m_spawnedEnemies.Add(character);

		FVector2D direction = FVector2D(1, 1);
		direction.Normalize();
		FVector resultDiretion = FVector(direction.X, direction.Y, 0);
		
		character->SetMoveToDirection(direction);
		character->SetLookAt(resultDiretion);
	}
}

