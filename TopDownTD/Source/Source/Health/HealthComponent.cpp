#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	MaxHealth = 100;
	CurrentHealth = 100;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	AActor* owner = GetOwner();
	owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);

	IsInitialized = true;
	OnComponentInitializeDelegate.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                       class AController* InstigatedBy,
                                       AActor* DamageCauser)
{
	Damage = FMath::Min(Damage, CurrentHealth);

	CurrentHealth -= Damage;
	
	if (IsDead())
	{
		OnDeath();
	}
	else
	{
		OnHealthChangeDelegate.Broadcast(CurrentHealth);
	}
}

void UHealthComponent::OnDeath()
{
	OnDieDelegate.Broadcast();
	
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

bool UHealthComponent::GetIsInitialized()
{
	return IsInitialized;
}
