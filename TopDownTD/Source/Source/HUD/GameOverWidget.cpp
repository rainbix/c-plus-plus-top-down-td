#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::InitializeWidget(int score)
{
	if (scoreText)
	{
		const FString costStr = FString::Printf(TEXT("Score: %d"), score);
		scoreText->SetText(FText::FromString(costStr));
	}

	if (replayButton)
		replayButton->OnClicked.AddDynamic(this, &UGameOverWidget::ReplayPressHandler);

	if (mainMenuButton)
		mainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::MainMenuPressHandler);
}

void UGameOverWidget::ReplayPressHandler()
{
	if (gameLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), gameLevel);
}

void UGameOverWidget::MainMenuPressHandler()
{
	if (mainMenuLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), mainMenuLevel);
}
