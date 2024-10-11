// Fill out your copyright notice in the Description page of Project Settings.

#include "Source/Public/PlayerCharacterSource.h"
#include "Source/Health/HealthComponent.h"
#include "Source/Weapons/WeaponComponent.h"

APlayerCharacterSource::APlayerCharacterSource()
{
	moveSpeed = 1;
	mouseRotationSpeed = 2;
	
	//Health
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
}

void APlayerCharacterSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!m_moveDirection.IsZero())
	{
		MoveToDirection(m_moveDirection);
	}
	
	if (!m_lookDirection.IsZero())
	{
		LookAt(m_lookDirection, mouseRotationSpeed, DeltaTime);
	}
}

void APlayerCharacterSource::MoveToDirection(FVector2D direction)
{
	FVector moveDir = FVector(direction.X, direction.Y, 0);
	AddMovementInput(moveDir, moveSpeed);
}

void APlayerCharacterSource::LookAt(FVector direction, float speed, float deltaTime)
{
	FRotator currentRotation = GetActorRotation();
	FRotator desiredRotation = currentRotation;
	desiredRotation.Yaw = direction.Rotation().Yaw;

	currentRotation = FMath::RInterpTo(currentRotation, desiredRotation, deltaTime, speed);

	SetActorRotation(currentRotation);
}

void APlayerCharacterSource::SetMoveToDirection(FVector2D direction)
{
	m_moveDirection = direction;
}

void APlayerCharacterSource::SetLookAt(FVector direction)
{
	m_lookDirection = direction;
}

UHealthComponent* APlayerCharacterSource::GetHealthComponent() const
{
	return HealthComponent;
}

UWeaponComponent* APlayerCharacterSource::GetWeaponComponent() const
{
	return WeaponComponent;
}
