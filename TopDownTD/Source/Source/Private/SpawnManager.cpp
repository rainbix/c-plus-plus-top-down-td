// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnManager.h"
#include "PlayerCharacterSource.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	spawnInterval = 5;
	decreaseSpawnIntervalOverTime = 0;
	decreaseSpawnIntervalValue = 0;
	minimumSpawnInterval = 1;
	maxSpawnCount = 5;
	
	m_currentSpawnInterval = 0;
	m_currentDecreaseTime = 0;
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_currentDelay += DeltaTime;
	m_currentSpawnInterval += DeltaTime;
	m_currentDecreaseTime += DeltaTime;

	if (m_currentDelay < firstSpawnDelay)
	{
		return;
	}

	if (m_currentSpawnInterval >= spawnInterval && m_spawnedEnemies.Num() < maxSpawnCount)
	{
		m_currentDecreaseTime += m_currentSpawnInterval;

		if (m_currentDecreaseTime >= decreaseSpawnIntervalOverTime)
		{
			m_currentDecreaseTime -= decreaseSpawnIntervalOverTime;
			spawnInterval = FMath::Max(spawnInterval - decreaseSpawnIntervalValue, minimumSpawnInterval);
		}
		
		m_currentSpawnInterval = 0;

		FVector spawnLocation = GetActorLocation();

		if (!locationRandomRange.IsNearlyZero())
		{
			spawnLocation.X += FMath::RandRange(-locationRandomRange.X, locationRandomRange.X);
			spawnLocation.Y += FMath::RandRange(-locationRandomRange.Y, locationRandomRange.Y);
		}

		SpawnCharacter(spawnLocation);
	}
}

void ASpawnManager::SpawnCharacter(FVector location)
{
	FRotator rotator = FRotator::ZeroRotator;
	FActorSpawnParameters spawnInfo;
		
	APlayerCharacterSource* character =
		GetWorld()->SpawnActor<APlayerCharacterSource>(characterPrefab, location, rotator, spawnInfo);

	m_spawnedEnemies.Add(character);

	FVector2D direction;
	if (destinationLocation)
	{
		FVector destination = destinationLocation->GetActorLocation();
		FVector delta = destination - location;
		direction = FVector2D(delta.X, delta.Y);
	}
	else
	{
		direction = FVector2D(-1, 0);
	}
	
	direction.Normalize();
	FVector resultDirection = FVector(direction.X, direction.Y, 0);
		
	character->SetMoveToDirection(direction);
	character->SetLookAt(resultDirection);
}

