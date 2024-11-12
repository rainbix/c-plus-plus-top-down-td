#include "GameplayGameState.h"

void AGameplayGameState::BeginPlay()
{
	Super::BeginPlay();

	CurrentMoney = InitialMoney;
}

void AGameplayGameState::AddMoney(int amount)
{
	CurrentMoney += amount;

	OnMoneyAdded.Broadcast(amount, CurrentMoney);
}

void AGameplayGameState::RemoveMoney(int amount)
{
	const int newMoneyValue = CurrentMoney - amount;
	CurrentMoney = FMath::Clamp(newMoneyValue, 0, newMoneyValue);

	OnMoneyRemoved.Broadcast(amount, CurrentMoney);
}

int AGameplayGameState::GetCurrentMoney() const
{
	return CurrentMoney;
}

bool AGameplayGameState::HasEnoughMoney(int price) const
{
	return GetCurrentMoney() >= price;
}
