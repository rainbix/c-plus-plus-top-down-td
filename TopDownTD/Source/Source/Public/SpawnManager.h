// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacterSource.h"
#include "SpawnManager.generated.h"

UCLASS()
class SOURCE_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterDied, APlayerCharacterSource*)
	FOnCharacterDied OnCharacterDied;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float spawnInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float decreaseSpawnIntervalOverTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float decreaseSpawnIntervalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float minimumSpawnInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float firstSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	int maxSpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	AActor* destinationLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	TSubclassOf<APlayerCharacterSource> characterPrefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	FVector2f locationRandomRange;
	
	// Sets default values for this actor's properties
	ASpawnManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void SpawnCharacter(FVector location);
	void HandleCharacterDieEvent(AActor* senderActor);
	int CalculateMoneyForEnemy(int counter);
	int CalculateScoreForEnemy(int counter);

	static int totalSpawnIterations;
	float m_currentDelay;
	float m_currentSpawnInterval;
	float m_currentDecreaseTime;
	TArray<APlayerCharacterSource*> m_spawnedEnemies;
};
