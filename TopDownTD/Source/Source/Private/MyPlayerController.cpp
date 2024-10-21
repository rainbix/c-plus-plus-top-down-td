// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include <Source/Weapons/WeaponComponent.h>

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacterSource.h"

AMyPlayerController::AMyPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMouseInput(DeltaTime);
}

void AMyPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (USourceAbilitySystemComponent* SourceASC = GetSourceAbilitySystemComponent())
	{
		SourceASC->ProcessAbilityInput();
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);
	
	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		subsystem->ClearAllMappings();
		subsystem->AddMappingContext(mappingContext, 1);
	}
	
	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	inputComponent->BindAction(moveInput, ETriggerEvent::Triggered, this, &AMyPlayerController::HandleMovementInput);

	if (InputConfig)
	{
		for (FInputActionTag InputTagAction : InputConfig->AbilityInputActions)
		{
			inputComponent->BindAction(InputTagAction.InputAction, ETriggerEvent::Started, this, &ThisClass::AbilityInputTagPressed, InputTagAction.InputTag);
			inputComponent->BindAction(InputTagAction.InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputTagReleased, InputTagAction.InputTag);
		}		
	}
	//Build
	inputComponent->BindAction(buildInput, ETriggerEvent::Started, this, &AMyPlayerController::HandleBuildPressed);
}

USourceAbilitySystemComponent* AMyPlayerController::GetSourceAbilitySystemComponent() const
{
	USourceAbilitySystemComponent* SourceASC = nullptr;
	
	if (const APawn* ControlledPawn = GetPawn())
	{
		if (const ISourceAbilitySystemInterface* AscInterface = Cast<ISourceAbilitySystemInterface>(ControlledPawn))
		{
			SourceASC = AscInterface->GetSourceAbilitySystemComponent();
		}
	}

	return SourceASC;
}

void AMyPlayerController::HandleMovementInput(const FInputActionValue& value)
{
	APawn* controlledPawn = GetPawn();

	if (!controlledPawn)
	{
		return;
	}
	
	APlayerCharacterSource* player = Cast<APlayerCharacterSource>(controlledPawn);
	
	const FVector2D moveVector = value.Get<FVector2D>();
	player->MoveToDirection(moveVector);
}

void AMyPlayerController::HandleMouseInput(float deltaTime)
{
	APawn* controlledPawn = GetPawn();

	if (!controlledPawn)
	{
		return;
	}

	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_WorldStatic, true, hitResult);
	
	APlayerCharacterSource* player = Cast<APlayerCharacterSource>(controlledPawn);
	
	FVector const charPosition = player->GetActorLocation();
	FVector directionToMouse = hitResult.Location - charPosition;
	directionToMouse.Normalize();

	player->LookAt(directionToMouse, player->mouseRotationSpeed, deltaTime);
}

void AMyPlayerController::AbilityInputTagPressed(FGameplayTag GameplayTag)
{
	if (USourceAbilitySystemComponent* ASC = GetSourceAbilitySystemComponent())
	{
		ASC->AbilityInputTagPressed(GameplayTag);
	}
}


void AMyPlayerController::AbilityInputTagReleased(FGameplayTag GameplayTag)
{
	if (USourceAbilitySystemComponent* ASC = GetSourceAbilitySystemComponent())
	{
		ASC->AbilityInputTagReleased(GameplayTag);
	}
}


void AMyPlayerController::HandleBuildPressed()
{
	OnBuildInputDelegate.Broadcast();
}