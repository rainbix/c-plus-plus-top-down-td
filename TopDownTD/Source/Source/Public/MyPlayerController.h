// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Source/SourcePlayerController.h"
#include "Source/AbilitySystem/SourceAbilitySystemComponent.h"
#include "Source/Input/InputConfig.h"
#include "MyPlayerController.generated.h"

enum class EAbilityInputID : int8;

UCLASS()
class SOURCE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* moveInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* buildInput;

	AMyPlayerController();
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	DECLARE_MULTICAST_DELEGATE(FOnBuildInput)
	FOnBuildInput OnBuildInputDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UInputConfig> InputConfig;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;


private:
	USourceAbilitySystemComponent* GetSourceAbilitySystemComponent() const;
	void HandleMovementInput(const FInputActionValue& value);
	void HandleMouseInput(float deltaTime);
	void AbilityInputTagPressed(FGameplayTag GameplayTag);
	void AbilityInputTagReleased(FGameplayTag GameplayTag);
	void HandleBuildPressed();
};
