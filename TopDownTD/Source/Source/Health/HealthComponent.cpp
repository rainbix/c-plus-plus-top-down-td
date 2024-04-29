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
