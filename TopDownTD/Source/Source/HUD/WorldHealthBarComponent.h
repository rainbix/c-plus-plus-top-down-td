// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldHealthBarComponent.generated.h"

class UProgressBarWidget;
class UHealthComponent;

//To add a world health bar widget to an Actor do the following steps:
//1. Add Health component
//2. Add World Health Bar component
//3. Add Widget component
//4. In widget component under User Interface:
//     - assign desired HealthBar widget at WidgetClass 
//     - check Draw at Desired Size checkbox
//See 'BP_WorldHealthbarExample' as example

//Note, Health Bar Widget works only in conjunction with Health component

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOURCE_API UWorldHealthBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWorldHealthBarComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:	

	UPROPERTY()
	UProgressBarWidget* HealthBarWidget;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	#pragma region Initialization
	
	bool TryGetHealthBarWidget();
	bool TryGetHealthComponent();
	void BindHealthBarWidgetToHealthComponent();

	#pragma endregion 

	#pragma region Event Handlers
	
	void HealthInitializeHandler(int currentHealth, int maxHealth);
	void HealthChangedHandler(int currentHealth);
	void DieHandler();

	#pragma endregion
};
