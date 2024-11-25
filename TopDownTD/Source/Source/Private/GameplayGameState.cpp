#include "GameplayGameState.h"
#include "ProfitHolderComponent.h"

void AGameplayGameState::BeginPlay()
{
	Super::BeginPlay();

	currentMoney = InitialMoney;
	currentScore = 0;
}

#pragma region Money

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

#pragma region FinishGame

void AGameplayGameState::FinishGame() const
{
	OnGameFinished.Broadcast(GetScore());
}

#pragma endregion

#pragma region Profit

void AGameplayGameState::ProcessEnemyKill(const AActor* killedActor)
{
	if (!killedActor)
		return;
	
	FetchProfit(killedActor->GetComponentByClass<UProfitHolderComponent>());
}

void AGameplayGameState::FetchProfit(const UProfitHolderComponent* profitComponent)
{
	if (!profitComponent)
		return;
	
		AddMoney(profitComponent->GetMoney());
		AddScore(profitComponent->GetScore());
}

#pragma endregion 
