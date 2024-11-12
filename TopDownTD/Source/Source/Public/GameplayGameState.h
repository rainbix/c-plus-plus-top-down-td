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

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoneyAdd, int delta, int newAmount)
	FOnMoneyAdd OnMoneyAdded;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoneyRemove, int delta, int newAmount)
	FOnMoneyRemove OnMoneyRemoved;
	
	void AddMoney(int amount);
	void RemoveMoney(int amount);
	int GetCurrentMoney() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Money")
	int InitialMoney;

	UPROPERTY(VisibleDefaultsOnly, Category="Money")
	int CurrentMoney;
};
