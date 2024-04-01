#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

class UTextBlock;
class UGridSlot;

#pragma region Public

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ProcessDisplayParticipants(InDeltaTime);
}

#pragma endregion

#pragma region Protected

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (playButton)
		playButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayButtonPressHandler);
	
	if (gymButton)
		gymButton->OnClicked.AddDynamic(this, &UMainMenuWidget::GymButtonPressHandler);
	
	if (creditsButton)
		creditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::CreditsButtonPressHandler);
	
	if (exitButton)
		exitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitButtonPressHandler);

	if (backFromCreditsButton)
		backFromCreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::BackFromCreditsButtonHandler);

	PopulateParticipants();
	ToViewMode(EViewModes::MainView);
}

#pragma endregion 

#pragma region Private

#pragma region ButtonHandlers

void UMainMenuWidget::PlayButtonPressHandler()
{
	if (gameLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), gameLevel);
	else 
		PrintScreenMessage(TEXT("Game level is not assigned"), FColor::Red);
}

void UMainMenuWidget::GymButtonPressHandler()
{
	if (gymLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), gymLevel);
	else 
		PrintScreenMessage(TEXT("Gym level is not assigned"), FColor::Yellow);
}

void UMainMenuWidget::CreditsButtonPressHandler()
{
	ToViewMode(EViewModes::CreditsView);
}

void UMainMenuWidget::ExitButtonPressHandler()
{
	GetOwningPlayer()->ConsoleCommand("exit");
}

void UMainMenuWidget::BackFromCreditsButtonHandler()
{
	ToViewMode(EViewModes::MainView);
}

#pragma endregion

#pragma region Participants

void UMainMenuWidget::PopulateParticipants()
{
	//Reserve array capacity
	participants.Reserve(participantNames.Num());
	participantsToShow.Reserve(participantNames.Num());
	
	//Populate participants
	for (int i = 0; i < participantNames.Num(); i++)
	{
		participantsToShow.Add(i);
		
		int row = i / 2;
		int col = i % 2;
		
		CreateParticipant(participantNames[i], row, col);
	}
}

void UMainMenuWidget::CreateParticipant(const FString& name, int32 row, int32 column)
{
	//Create new block
	UTextBlock* textBlock = NewObject<UTextBlock>(this);
	textBlock->SetText(FText::FromString(name));
	textBlock->SetVisibility(ESlateVisibility::Hidden);
	
	//Add the text block to the grid panel
	creditsGridPanel->AddChild(textBlock);

	//Create a grid slot
	UGridSlot* gridSlot = creditsGridPanel->AddChildToGrid(textBlock);

	//Set the row and column for the text block
	gridSlot->SetRow(row);
	gridSlot->SetColumn(column);
	gridSlot->SetPadding(50);
	
	//add to participants list
	participants.Add(textBlock);
}

void UMainMenuWidget::CleanupDisplayedParticipants()
{
	isParticipantDisplayFlowActive = false;
	participantFlowCurTime = 0;
	participantsToShow.Reset();
	
	for (int i = 0; i < participants.Num(); i++)
	{
		participantsToShow.Add(i);
		
		if (participants[i])
			participants[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainMenuWidget::ProcessDisplayParticipants(float InDeltaTime)
{
	if (!isParticipantDisplayFlowActive)
		return;

	participantFlowCurTime += InDeltaTime;
	if (participantFlowCurTime > timeToNextParticipant)
	{
		participantFlowCurTime = 0;

		//Get random participant index
		const int rndIndex = FMath::RandRange(0, participantsToShow.Num() - 1);

		//Get participant
		const int i = participantsToShow[rndIndex];

		//Enable participant
		participants[i]->SetVisibility(ESlateVisibility::Visible);
		participantsToShow.RemoveAt(rndIndex);

		//Generate rnd color
		float r = FMath::RandRange(0.f, 1.f);
		float g = FMath::RandRange(0.f, 1.f);
		float b = FMath::RandRange(0.f, 1.f);

		//Apply rnd color to participant
		FSlateColor rndColor = FSlateColor(FLinearColor(r, g, b, 1.0f));
		participants[i]->SetColorAndOpacity(rndColor);

		PrintScreenMessage(FString::FromInt(i));
		
		//Stop flow if all participants were shown
		if (participantsToShow.Num() == 0)
			isParticipantDisplayFlowActive = false;
	}
}

#pragma endregion

#pragma region Tools

void UMainMenuWidget::ToViewMode(EViewModes viewMode)
{
	switch (viewMode)
	{
		case EViewModes::MainView:
			mainVerticalBox->SetVisibility(ESlateVisibility::Visible);
			creditsVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
		
			CleanupDisplayedParticipants();
		
			break;

		case EViewModes::CreditsView:
			mainVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
			creditsVerticalBox->SetVisibility(ESlateVisibility::Visible);

			isParticipantDisplayFlowActive = true;
		
			break;
	}
}

void UMainMenuWidget::PrintScreenMessage(const FString& message, FColor color, float duration)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, duration, color, message);
}

#pragma endregion

#pragma endregion
