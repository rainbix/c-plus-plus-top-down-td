// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnManager.h"
#include "GameplayGameState.h"
#include "PlayerCharacterSource.h"
#include "ProfitHolderComponent.h"
#include "Source/Health/HealthComponent.h"
#include "Source/Tools/GeneralPurposeUtils.h"

int ASpawnManager::totalSpawnIterations = 0;

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

	totalSpawnIterations = 0;
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

		totalSpawnIterations++;
		SpawnCharacter(spawnLocation);
	}
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	//Reset spawn iterations
	totalSpawnIterations = 0;
}

void ASpawnManager::SpawnCharacter(FVector location)
{
	const FRotator rotator = FRotator::ZeroRotator;
	FActorSpawnParameters spawnInfo;

	const auto character = GetWorld()->SpawnActor<APlayerCharacterSource>(characterPrefab, location, rotator, spawnInfo);

	m_spawnedEnemies.Add(character);

	FVector2D direction;
	if (destinationLocation)
	{
		const FVector destination = destinationLocation->GetActorLocation();
		const FVector delta = destination - location;
		direction = FVector2D(delta.X, delta.Y);
	}
	else
	{
		direction = FVector2D(-1, 0);
	}
	
	direction.Normalize();
	const FVector resultDirection = FVector(direction.X, direction.Y, 0);
		
	character->SetMoveToDirection(direction);
	character->SetLookAt(resultDirection);

	//Add profit
	const auto profitComponent = NewObject<UProfitHolderComponent>(character);
	profitComponent->InitializeData(
		CalculateMoneyForEnemy(totalSpawnIterations),
		CalculateScoreForEnemy(totalSpawnIterations));
	
	character->AddInstanceComponent(profitComponent);

	//Enemy death event
	if (const auto healthComponent = character->GetHealthComponent())
	{
		healthComponent->OnDieDelegate.AddUObject(this, &ASpawnManager::HandleCharacterDieEvent);
	}
}

void ASpawnManager::HandleCharacterDieEvent(AActor* senderActor)
{
	if (const auto gameState = GetWorld()->GetGameState<AGameplayGameState>())
		gameState->ProcessEnemyKill(senderActor);
}

int ASpawnManager::CalculateMoneyForEnemy(int counter)
{ 
	const int baseAmount = 3;
	const int deltaAmount = FMath::RandRange(1, 2);
	const int incrementThreshold = 10; // Increment money each N enemies 
	
	return baseAmount + deltaAmount * (counter / incrementThreshold);
}

int ASpawnManager::CalculateScoreForEnemy(int counter)
{
	const int baseAmount = 1;
	const int extraAmount = 1;
	const int extraThreshold = 10; // Increment money each N enemies 

	if (counter % extraThreshold == 0)
		return baseAmount + extraAmount;
	
	return baseAmount;
}

