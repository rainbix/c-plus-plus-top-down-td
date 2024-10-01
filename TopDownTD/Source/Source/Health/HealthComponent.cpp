#include "HealthComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Source/AbilitySystem/Attibutes/HealthSet.h"

DECLARE_LOG_CATEGORY_EXTERN(Health, Log, All);
DEFINE_LOG_CATEGORY(Health);

UHealthComponent::UHealthComponent()
{
	HealthSet = nullptr;
	IsInitialized = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UAbilitySystemComponent* ASC = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();

	if (!IsValid(ASC))
	{
		UE_LOG(Health, Error, TEXT("HealthComponent: Health component for owner [%s] doesn't have ability system."), *GetNameSafe(GetOwner()));
		return;
	}

	HealthSet = ASC->GetSet<UHealthSet>();
	if (!HealthSet)
	{
		UE_LOG(Health, Error, TEXT("HealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(GetOwner()));
		return;
	}

	HealthSet->OnCurrentHealthChanged.AddUObject(this, &UHealthComponent::HandleCurrentHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &UHealthComponent::HandleMaxHealthChanged);

	HandleMaxHealthChanged(GetMaxHealth());
	HandleCurrentHealthChanged(GetMaxHealth());
}

void UHealthComponent::HandleCurrentHealthChanged(float NewValue)
{
	OnCurrentHealthChangeDelegate.Broadcast(NewValue);

	if (HealthSet->GetCurrentHealth() < 0.0f)
	{
		OnDeath();
	}
}

void UHealthComponent::HandleMaxHealthChanged(float NewValue)
{
	OnMaxHealthChangeDelegate.Broadcast(NewValue);
}

void UHealthComponent::OnDeath()
{
	OnDieDelegate.Broadcast();
	
	GetOwner()->Destroy();
}

bool UHealthComponent::IsDead()
{
	return HealthSet->GetCurrentHealth() <= 0;
}

int UHealthComponent::GetCurrentHealth()
{
	return HealthSet ? HealthSet->GetCurrentHealth() : 0;
}

int UHealthComponent::GetMaxHealth()
{
	return HealthSet ? HealthSet->GetMaxHealth() : 0;
}

bool UHealthComponent::GetIsInitialized()
{
	return IsInitialized;
}
