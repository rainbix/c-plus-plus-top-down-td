// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100;
	CurrentHealth = 100;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	AActor* owner = GetOwner();
	owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                       class AController* InstigatedBy,
                                       AActor* DamageCauser)
{
	Damage = FMath::Min(Damage, CurrentHealth);

	CurrentHealth -= Damage;

	// UE_LOG(LogTemp, Log, TEXT("Health %i"), CurrentHealth);

	if (IsDead())
	{
		OnDeath();
	}
}

void UHealthComponent::OnDeath()
{
	GetOwner()->Destroy();
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
