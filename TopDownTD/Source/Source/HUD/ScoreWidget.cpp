#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(int delta, int newAmount)
{
	if (currentScoreText)
	{
		const FString costStr = FString::Printf(TEXT("Score: %d"), newAmount);
		currentScoreText->SetText(FText::FromString(costStr));
	}
}
