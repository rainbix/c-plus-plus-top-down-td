// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
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
	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_WorldStatic, true, hitResult);

	APawn* controlledPawn = GetPawn();

	if (!controlledPawn)
	{
		return;
	}
	
	APlayerCharacterSource* player = Cast<APlayerCharacterSource>(controlledPawn);
	
	FVector const charPosition = player->GetActorLocation();
	FVector directionToMouse = hitResult.Location - charPosition;
	directionToMouse.Normalize();

	player->LookAt(directionToMouse, player->mouseRotationSpeed, deltaTime);
}
