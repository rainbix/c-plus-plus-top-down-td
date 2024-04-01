#include "MainMenuWidget.h"

#include "ParticipantWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Source/Tools/GeneralPurposeUtils.h"

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

	#pragma region Button Handlers
	
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

	#pragma endregion 
	
	world = GetWorld();
	interpolator = MakeUnique<Interpolator>(timeToNextParticipant);
	
	PopulateParticipants();
	ToViewMode(EViewModes::MainView);
}

#pragma endregion 

#pragma region Private

#pragma region ButtonHandlers

void UMainMenuWidget::PlayButtonPressHandler()
{
	if (gameLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(world, gameLevel);
	else 
		GeneralPurposeUtils::DisplayScreenMessage(TEXT("Gym level is not assigned"), FColor::Yellow);
}

void UMainMenuWidget::GymButtonPressHandler()
{
	if (gymLevel)
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), gymLevel);
	else
		GeneralPurposeUtils::DisplayScreenMessage(TEXT("Gym level is not assigned"), FColor::Yellow);
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
	participantsWidgets.Reserve(participantNames.Num());
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

	TObjectPtr<UParticipantWidget> widget = CreateWidget<UParticipantWidget>(world, participantWidgetTemplate);
	widget->SetParticipantName(FText::FromString(name));
	widget->SetVisibility(ESlateVisibility::Hidden);
	
	//Add the text block to the grid panel
	creditsGridPanel->AddChild(widget);

	//Create a grid slot
	UGridSlot* gridSlot = creditsGridPanel->AddChildToGrid(widget);

	//Set the row and column for the text block
	gridSlot->SetRow(row);
	gridSlot->SetColumn(column);
	gridSlot->SetPadding(50);
	
	//add to participants list
	participantsWidgets.Add(widget);
}

void UMainMenuWidget::CleanupDisplayedParticipants()
{
	interpolator->Stop();
	participantsToShow.Reset();
	
	for (int i = 0; i < participantsWidgets.Num(); i++)
	{
		participantsToShow.Add(i);
		
		if (participantsWidgets[i])
			participantsWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainMenuWidget::ProcessDisplayParticipants(float InDeltaTime)
{
	if (!interpolator->IsActive())
		return;

	interpolator->ProcessTick(InDeltaTime);
	
	if (interpolator->IsElapsed())
	{
		interpolator->Reset();

		//Get random participant index
		const int rndIndex = FMath::RandRange(0, participantsToShow.Num() - 1);

		//Get participant
		const int i = participantsToShow[rndIndex];

		//Enable participant
		participantsWidgets[i]->SetVisibility(ESlateVisibility::Visible);
		participantsToShow.RemoveAt(rndIndex);

		//Generate rnd color
		const FSlateColor rndColor = GetRandomSlateColor();
		const FLinearColor rndLinearColor = GetRandomLinearColor(0.25f);

		//Apply rnd color to participant
		participantsWidgets[i]->SetNameStyle(rndColor);
		participantsWidgets[i]->SetBackgroundStyle(rndLinearColor);
		
		//Stop flow if all participants were shown
		if (participantsToShow.Num() == 0)
			interpolator->Stop();
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

			interpolator->Start();
		
			break;
	}
}

RGB UMainMenuWidget::GenerateRandomRGB()
{
	float r = FMath::RandRange(0.f, 1.f);
	float g = FMath::RandRange(0.f, 1.f);
	float b = FMath::RandRange(0.f, 1.f);

	return RGB(r, g, b);
}

FLinearColor UMainMenuWidget::GetRandomLinearColor(float alpha)
{
	RGB rgb = GenerateRandomRGB();

	return  FLinearColor(rgb.r, rgb.g, rgb.b, alpha);
}

FSlateColor UMainMenuWidget::GetRandomSlateColor(float alpha)
{
	return  FSlateColor(GetRandomLinearColor(alpha));
}

#pragma endregion

#pragma endregion
