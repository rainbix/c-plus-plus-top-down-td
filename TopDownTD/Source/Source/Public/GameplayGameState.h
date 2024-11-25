#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameplayGameState.generated.h"

class UProfitHolderComponent;

UCLASS()
class SOURCE_API AGameplayGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	#pragma region Money
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoneyAdd, int delta, int newAmount)
	FOnMoneyAdd OnMoneyAdded;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoneyRemove, int delta, int newAmount)
	FOnMoneyRemove OnMoneyRemoved;

	UPROPERTY(EditDefaultsOnly, Category="Money")
	int InitialMoney;

	void AddMoney(int amount);
	void RemoveMoney(int amount);
	int GetCurrentMoney() const;
	bool HasEnoughMoney(int price) const;

	#pragma endregion

	#pragma region Score

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreAdded, int delta, int newAmount)
	FOnScoreAdded OnScoreAdded;
	
	void AddScore(int amount);
	int GetScore() const;

	#pragma endregion
	
	#pragma region FinishGame
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameFinished, int score)
	FOnGameFinished OnGameFinished;
	
	void FinishGame() const;

	#pragma endregion

	#pragma region Profit

	void FetchProfit(const UProfitHolderComponent* profitComponent);
	void ProcessEnemyKill(const AActor* killedActor);
	
	#pragma endregion 
	
protected:
	virtual void BeginPlay() override;

private:
	int currentScore;
	int currentMoney;
};
