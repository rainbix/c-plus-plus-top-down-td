#include "HealthComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectExtension.h"
#include "Source/AbilitySystem/Attibutes/HealthAttributeSet.h"

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

	HealthSet = ASC->GetSet<UHealthAttributeSet>();
	if (!HealthSet)
	{
		UE_LOG(Health, Error, TEXT("HealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(GetOwner()));
		return;
	}
	
	ASC->SetNumericAttributeBase(HealthSet->GetCurrentHealthAttribute(), HealthSet->GetMaxHealth());
	
	ASC->GetGameplayAttributeValueChangeDelegate(HealthSet->GetCurrentHealthAttribute()).AddUObject(this, &ThisClass::HandleCurrentHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(HealthSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);

	UE_LOG(Health, Display, TEXT("HealthComponent: MaxHealth [%f] CurrentHealth: [%f} for owner: [%s]."), HealthSet->GetMaxHealth(), HealthSet->GetCurrentHealth(), *GetNameSafe(GetOwner()));

	IsInitialized = true;

	OnComponentInitializeDelegate.Broadcast(HealthSet->GetCurrentHealth(), HealthSet->GetMaxHealth());
}

void UHealthComponent::HandleCurrentHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{

	UE_LOG(Health, Display, TEXT("HealthComponent: CurrentHealth changed to: [%f} for owner: [%s]."), HealthSet->GetCurrentHealth(), *GetNameSafe(GetOwner()));

	OnCurrentHealthChangeDelegate.Broadcast(OnAttributeChangeData.NewValue);

	if (HealthSet->GetCurrentHealth() <= 0.0f)
	{
		OnDeath();
	}
}

void UHealthComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	UE_LOG(Health, Display, TEXT("HealthComponent: MaxHealth changed to: [%f} for owner: [%s]."), HealthSet->GetMaxHealth(), *GetNameSafe(GetOwner()));

	OnMaxHealthChangeDelegate.Broadcast(OnAttributeChangeData.NewValue);
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
