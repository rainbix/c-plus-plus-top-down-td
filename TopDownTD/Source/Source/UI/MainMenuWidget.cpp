#include "MainMenuWidget.h"

#include "Source/Tools/SimpleInterpolator.h"
#include "ParticipantWidget.h"
#include "Components/VerticalBox.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/GridSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Source/Tools/GeneralPurposeUtils.h"
#include "Source/Tools/Interpolator.cpp"

#pragma region Public

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ProcessDisplayParticipants(InDeltaTime);
	AnimateBackgroundColor(InDeltaTime);
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
	participantsInterpolator = MakeUnique<SimpleInterpolator>(timeToNextParticipant);
	backgroundInterpolator = MakeUnique<Interpolator<FLinearColor>>(backgroundIdleTime, GetRandomLinearColor(), GetRandomLinearColor());
	backgroundInterpolator->Start();
	
	PopulateParticipants();
	ToViewMode(EViewModes::MainView);
}

#pragma endregion 

#pragma region Private

void UMainMenuWidget::AnimateBackgroundColor(float deltaTime)
{
	if (!backgroundInterpolator)
		return;
	
	backgroundInterpolator->ProcessTick(deltaTime);

	//Lerp color only if in transition mode
	if (isBackgroundTransitioning)
	{
		const auto color = FLinearColor::LerpUsingHSV(backgroundInterpolator->From, backgroundInterpolator->To, backgroundInterpolator->Progress());
		backgroundImage->SetColorAndOpacity(color);
	}

	if (backgroundInterpolator->IsElapsed())
	{
		//Toggle mode and set new state duration
		isBackgroundTransitioning = !isBackgroundTransitioning;
		backgroundInterpolator->ResetWithNewTime(isBackgroundTransitioning ? backgroundTransitionTime : backgroundIdleTime);

		//Calculate next target for transition
		if (isBackgroundTransitioning)
		{
			backgroundInterpolator->From = backgroundImage->GetColorAndOpacity();
			backgroundInterpolator->To = GetRandomLinearColor(backgroundInterpolator->From.A);
		}
	}
}

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
	participantsInterpolator->Stop();
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
	if (!participantsInterpolator->IsActive())
		return;

	participantsInterpolator->ProcessTick(InDeltaTime);
	
	if (participantsInterpolator->IsElapsed())
	{
		participantsInterpolator->Reset();

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
			participantsInterpolator->Stop();
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

			participantsInterpolator->Start();
		
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
