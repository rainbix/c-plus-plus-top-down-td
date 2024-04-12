// Copyright Epic Games, Inc. All Rights Reserved.

#include "SourceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ASourceCharacter::ASourceCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Health
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASourceCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// TimeSinceLastDamage += DeltaSeconds;
	// if (TimeSinceLastDamage > 2)
	// {
	// 	TimeSinceLastDamage = 0;
	// 	const FDamageInformation damageInfo(1);
	// 	Execute_ReceiveDamage(this, damageInfo);
	// }
}

void ASourceCharacter::ReceiveDamage_Implementation(FDamageInformation DamageInfo)
{	
	HealthComponent->ReceiveDamage(DamageInfo);
}

bool ASourceCharacter::IsDead_Implementation()
{
	return HealthComponent->IsDead();
}

int ASourceCharacter::GetCurrentHealth_Implementation()
{
	return HealthComponent->GetCurrentHealth();
}

int ASourceCharacter::GetMaxHealth_Implementation()
{
	return HealthComponent->GetMaxHealth();
}

void ASourceCharacter::DoShit()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "not const");
}

void ASourceCharacter::Something_Implementation()
{
	DoShit();
}
