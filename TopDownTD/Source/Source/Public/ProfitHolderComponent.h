// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProfitHolderComponent.generated.h"

///Retains profit data for an enemy object or other profitable entity

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOURCE_API UProfitHolderComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void InitializeData(int money, int score);
	int GetMoney() const;
	int GetScore() const;

private:
	UPROPERTY(EditInstanceOnly, Category="Profit")
	int Money;

	UPROPERTY(EditInstanceOnly, Category="Profit")
	int Score;
};
