// Fill out your copyright notice in the Description page of Project Settings.

#include "Source/Public/PlayerCharacterSource.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerCharacterSource::APlayerCharacterSource()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mouseRotationSpeed = 2;
}

void APlayerCharacterSource::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void APlayerCharacterSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMouseInput(DeltaTime);
}

void APlayerCharacterSource::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* pc = Cast<APlayerController>(Controller);
	check(inputComponent && pc);

	ULocalPlayer* LocalPlayer = pc->GetLocalPlayer();
	check(LocalPlayer);
	
	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		subsystem->ClearAllMappings();
		subsystem->AddMappingContext(mappingContext, 1);
	}
	
	inputComponent->BindAction(moveInput, ETriggerEvent::Triggered, this, &APlayerCharacterSource::MoveForward);
}

void APlayerCharacterSource::MoveForward(const FInputActionValue& value)
{
	const FVector2D moveVector = value.Get<FVector2D>();
	MoveToDirection(moveVector);
}

void APlayerCharacterSource::MoveToDirection(FVector2D direction)
{
	FVector fwd = FVector(1, 0, 0);
	AddMovementInput(fwd, direction.X);

	FVector right = FVector(0, 1, 0);
	AddMovementInput(right, direction.Y);
}

void APlayerCharacterSource::LookAt(FVector direction, float speed, float deltaTime)
{
	FRotator currentRotation = GetActorRotation();
	FRotator desiredRotation = currentRotation;
	desiredRotation.Yaw = direction.Rotation().Yaw;

	currentRotation = FMath::RInterpTo(currentRotation, desiredRotation, deltaTime, speed);

	SetActorRotation(currentRotation);
}

void APlayerCharacterSource::HandleMouseInput(float deltaTime)
{
	UWorld* world = GetWorld();
	const APlayerController* playerController = world->GetFirstPlayerController();

	FHitResult hitResult;
	playerController->GetHitResultUnderCursor(ECC_WorldStatic, true, hitResult);
	
	FVector const charPosition = playerController->GetPawn()->GetActorLocation();
	FVector directionToMouse = hitResult.Location - charPosition;
	directionToMouse.Normalize();

	LookAt(directionToMouse, mouseRotationSpeed, deltaTime);
}