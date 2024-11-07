// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayGameState.h"

#include "Source/Tools/GeneralPurposeUtils.h"

void AGameplayGameState::BeginPlay()
{
	Super::BeginPlay();

	CurrentMoney = InitialMoney;
}

void AGameplayGameState::AddMoney(int amount)
{
	CurrentMoney += amount;
}

void AGameplayGameState::RemoveMoney(int amount)
{
	const int newMoneyValue = CurrentMoney - amount;
	CurrentMoney = FMath::Clamp(newMoneyValue, 0, newMoneyValue);
}

int AGameplayGameState::GetCurrentMoney() const
{
	return CurrentMoney;
}
