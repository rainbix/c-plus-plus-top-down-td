// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyWidget.generated.h"

class UTextBlock;

UCLASS()
class SOURCE_API UMoneyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitializeWidget(int initialAmount);
	void Add(int delta, int amount);
	void Remove(int delta, int amount);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* currentMoneyText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* deltaMoneyText;

	UPROPERTY(EditDefaultsOnly, Category = "Costumization")
	FLinearColor addColor;

	UPROPERTY(EditDefaultsOnly, Category = "Costumization")
	FLinearColor removeColor;
	
	void SetMoney(int newAmount);

	#pragma region Timer
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	float timerDuration;
	
	bool bIsTimerActive = false;
	float curTimerValue = 0;
	
	void StartTimer();
	void StopTimer();
	void ProcessTimer(float deltaTime);
	bool IsTimerActive();

	#pragma endregion 
};
