// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameplayGameState.generated.h"

UCLASS()
class SOURCE_API AGameplayGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category="Money")
	int CurrentMoney;

	void AddMoney(int amount);
	void RemoveMoney(int amount);
	int GetCurrentMoney() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Money")
	int InitialMoney;
};
