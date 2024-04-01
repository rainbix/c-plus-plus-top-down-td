#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Source/Tools/Interpolator.h"
#include "MainMenuWidget.generated.h"

class UParticipantWidget;
class UVerticalBox;
class UGridPanel;
class UButton;
class UTextBlock;
class UWorld;
class UImage;

UENUM(BlueprintType)
enum class EViewModes : uint8
{
	MainView,
	CreditsView
};

struct RGB
{
	float r;
	float g;
	float b;
};

UCLASS()
class SOURCE_API UMainMenuWidget : public UUserWidget
{
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	#pragma region Elements

	//Buttons
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

	//Containers
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* mainVerticalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* creditsVerticalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGridPanel* creditsGridPanel;

	//Assignables
	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* gameLevel;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UWorld* gymLevel;

	UPROPERTY(EditAnywhere, Category="Assignables")
	UImage* backgroundImage = nullptr;

	UPROPERTY(EditAnywhere, Category="Assignables")
	TSubclassOf<UParticipantWidget> participantWidgetTemplate = nullptr;

	//Data
	UPROPERTY(EditAnywhere, Category="Assignables | Data")
	TArray<FString> participantNames;

	UPROPERTY(EditAnywhere, Category="Assignables | Data")
	float timeToNextParticipant = .2f;

	UPROPERTY(EditAnywhere, Category="Assignables | Data")
	float backgroundTransitionTime = 1.f;

	UPROPERTY(EditAnywhere, Category="Assignables | Data")
	float backgroundIdleTime = 2.f;
	
	#pragma endregion 

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	EViewModes currentViewMode = EViewModes::MainView;

	UPROPERTY()
	UWorld* world;

	bool isBackgroundTransitioning = false;
	FLinearColor fromBackgroundColor;
	FLinearColor toBackgrounColor;
	TUniquePtr<Interpolator> participantsInterpolator = nullptr;
	TUniquePtr<Interpolator> backgroundInterpolator = nullptr;
	
	void AnimateBackgroundColor(float deltaTime);
	
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

	UPROPERTY()
	TArray<UParticipantWidget*> participantsWidgets;

	UPROPERTY()
	TArray<int> participantsToShow;
	
	void PopulateParticipants();
	void CreateParticipant(const FString& name, int32 row, int32 column);
	void CleanupDisplayedParticipants();
	void ProcessDisplayParticipants(float InDeltaTime);

	#pragma endregion 

	#pragma region Tools
	
	void ToViewMode(EViewModes viewMode);

	RGB GenerateRandomRGB();
	FLinearColor GetRandomLinearColor(float alpha = 1.0f);
	FSlateColor GetRandomSlateColor(float alpha = 1.0f);

	#pragma endregion
	
	GENERATED_BODY()
};
