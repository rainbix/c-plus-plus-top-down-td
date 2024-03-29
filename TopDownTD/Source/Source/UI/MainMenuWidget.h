#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UVerticalBox;
class UGridPanel;
class UButton;
class UTextBlock;
class UWorld;

UENUM(BlueprintType)
enum class EViewModes : uint8
{
	MainView,
	CreditsView
};

UCLASS()
class SOURCE_API UMainMenuWidget : public UUserWidget
{
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	#pragma region Elements
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* playButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* gymButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* creditsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* exitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* backFromCreditsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* mainVerticalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* creditsVerticalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGridPanel* creditsGridPanel;

	UPROPERTY(EditAnywhere, Category="Assignables")
	TArray<FString> participantNames;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* gameLevel;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* gymLevel;
	
	#pragma endregion 

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	EViewModes currentViewMode = EViewModes::MainView;

	UPROPERTY()
	TArray<UTextBlock*> participants;

	UPROPERTY()
	TArray<int> participantsToShow;
	
	#pragma region ButtonHandlers
	
	UFUNCTION()
	void PlayButtonPressHandler();
	
	UFUNCTION()
	void GymButtonPressHandler();
	
	UFUNCTION()
	void CreditsButtonPressHandler();
	
	UFUNCTION()
	void ExitButtonPressHandler();

	UFUNCTION()
	void BackFromCreditsButtonHandler();

	#pragma endregion 

	#pragma region Participants
	
	bool isParticipantDisplayFlowActive = false;
	float participantFlowCurTime;
	const float timeToNextParticipant = 0.2f;
	
	void PopulateParticipants();
	void CreateParticipant(const FString& name, int32 row, int32 column);
	void CleanupDisplayedParticipants();
	void ProcessDisplayParticipants(float InDeltaTime);

	#pragma endregion 

	#pragma region Tools
	
	void ToViewMode(EViewModes viewMode);
	void PrintScreenMessage(const FString& message, FColor color = FColor::Yellow, float duration = 2.0);

	#pragma endregion
	
	GENERATED_BODY()
	
};
