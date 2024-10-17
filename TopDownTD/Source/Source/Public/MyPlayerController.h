// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Source/SourcePlayerController.h"
#include "MyPlayerController.generated.h"

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
	UInputAction* fireInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* reloadInput;

	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	void HandleMovementInput(const FInputActionValue& value);
	void HandleMouseInput(float deltaTime);
	void HandleFireInput();
	void HandleReloadInput();
};
