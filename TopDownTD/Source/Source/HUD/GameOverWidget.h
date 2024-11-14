#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SOURCE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void InitializeWidget(int score);
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* replayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* mainMenuButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* scoreText;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* gameLevel;
	
	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* mainMenuLevel;

	UFUNCTION()
	void ReplayPressHandler();
	
	UFUNCTION()
	void MainMenuPressHandler();
};
