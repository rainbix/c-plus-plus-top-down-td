// Copyright Epic Games, Inc. All Rights Reserved.

#include "SourcePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SourceCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASourcePlayerController::ASourcePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ASourcePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ASourcePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ASourcePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ASourcePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ASourcePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ASourcePlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ASourcePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ASourcePlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ASourcePlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ASourcePlayerController::OnTouchReleased);

		//Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ASourcePlayerController::Fire);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ASourcePlayerController::Reload);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASourcePlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ASourcePlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ASourcePlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ASourcePlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ASourcePlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ASourcePlayerController::Fire()
{
	ASourceCharacter* character = Cast<ASourceCharacter>(GetPawn());
	character->Fire();
}

void ASourcePlayerController::Reload()
{
	ASourceCharacter* character = Cast<ASourceCharacter>(GetPawn());
	character->Reload();
}
