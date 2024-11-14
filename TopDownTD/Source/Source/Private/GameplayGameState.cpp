#include "GameplayGameState.h"

#pragma region Money

void AGameplayGameState::BeginPlay()
{
	Super::BeginPlay();

	currentMoney = InitialMoney;
}

void AGameplayGameState::AddMoney(int amount)
{
	currentMoney += amount;

	OnMoneyAdded.Broadcast(amount, currentMoney);
}

void AGameplayGameState::RemoveMoney(int amount)
{
	const int newMoneyValue = currentMoney - amount;
	currentMoney = FMath::Clamp(newMoneyValue, 0, newMoneyValue);

	OnMoneyRemoved.Broadcast(amount, currentMoney);
}

int AGameplayGameState::GetCurrentMoney() const
{
	return currentMoney;
}

bool AGameplayGameState::HasEnoughMoney(int price) const
{
	return GetCurrentMoney() >= price;
}

#pragma endregion

#pragma region Score

void AGameplayGameState::AddScore(int amount)
{
	currentScore += amount;

	OnScoreAdded.Broadcast(amount, currentScore);
}

int AGameplayGameState::GetScore() const
{
	return currentScore;
}

#pragma endregion

void AGameplayGameState::FinishGame() const
{
	OnGameFinished.Broadcast(GetScore());
}


