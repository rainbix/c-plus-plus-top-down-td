#include "ProfitHolderComponent.h"

void UProfitHolderComponent::InitializeData(int money, int score)
{
	Money = money;
	Score = score;
}

int UProfitHolderComponent::GetMoney() const
{
	return Money;
}

int UProfitHolderComponent::GetScore() const
{
	return Score;
}
