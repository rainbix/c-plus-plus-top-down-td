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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float spawnInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	int maxSpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	TSubclassOf<APlayerCharacterSource> characterPrefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	FVector2f locationRandomRange;
	
	// Sets default values for this actor's properties
	ASpawnManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float m_currentSpawnInterval;
	TArray<APlayerCharacterSource*> m_spawnedEnemies;
};
