// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DamageInformation.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 10;
	CurrentHealth = 10;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComponent::ReceiveDamage(FDamageInformation& DamageInfo)
{
	CurrentHealth -= DamageInfo.Value;

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
	}
	
	// UE_LOG(LogTemp, Log, TEXT("Health %i"), CurrentHealth);
}

bool UHealthComponent::IsDead()
{
	return CurrentHealth <= 0;
}

int UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

