// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldHealthBarComponent.h"
#include "ProgressBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Source/Health/HealthComponent.h"

// Sets default values for this component's properties
UWorldHealthBarComponent::UWorldHealthBarComponent()
{
	
}

void UWorldHealthBarComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Try to get HealthBar Widget and Health Component
	if (TryGetHealthBarWidget() && TryGetHealthComponent())
	{
		//Bind widget to health component
		BindHealthBarWidgetToHealthComponent();
	}
}

void UWorldHealthBarComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UWorldHealthBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Possibly could be used for smooth progress bar lerping... ???
}

#pragma region Initialization

bool UWorldHealthBarComponent::TryGetHealthBarWidget()
{
	if (const auto healthWidgetComponent = GetOwner()->FindComponentByClass<UWidgetComponent>())
	{
		if (const auto owningHealthWidget = healthWidgetComponent->GetWidget())
		{
			HealthBarWidget = Cast<UProgressBarWidget>(owningHealthWidget);
			return true;
		}
	}

	return false;
}

bool UWorldHealthBarComponent::TryGetHealthComponent()
{
	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();
	return HealthComponent != nullptr;
}

void UWorldHealthBarComponent::BindHealthBarWidgetToHealthComponent()
{
	if (HealthComponent && HealthBarWidget)
	{
		//Handle undefined components initialization order
		if (HealthComponent->GetIsInitialized())
		{
			HealthBarWidget->InitializeWidget(HealthComponent->GetMaxHealth(), HealthComponent->GetCurrentHealth());
		}
		else
		{
			HealthComponent->OnComponentInitializeDelegate.AddUObject(this, &UWorldHealthBarComponent::HealthInitializeHandler);
		}

		HealthComponent->OnCurrentHealthChangeDelegate.AddUObject(this, &UWorldHealthBarComponent::HealthChangedHandler);
		HealthComponent->OnDieDelegate.AddUObject(this, &UWorldHealthBarComponent::DieHandler);
	}
}

#pragma endregion

#pragma region Event Handlers

void UWorldHealthBarComponent::HealthInitializeHandler(int currentHealth, int maxHealth)
{
	HealthBarWidget->InitializeWidget(currentHealth, maxHealth);
}

void UWorldHealthBarComponent::HealthChangedHandler(int newHealth)
{
	HealthBarWidget->SetValue(newHealth);
}

void UWorldHealthBarComponent::DieHandler()
{
}

#pragma endregion

