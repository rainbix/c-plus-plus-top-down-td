#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class SOURCE_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateScore(int delta, int newAmount);
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* currentScoreText;
};
