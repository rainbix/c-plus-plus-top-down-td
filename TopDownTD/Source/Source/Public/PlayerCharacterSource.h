// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Source/SourcePlayerController.h"
#include "AbilitySystemInterface.h"
#include "PlayerCharacterSource.generated.h"

UCLASS()
class SOURCE_API APlayerCharacterSource : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float mouseRotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* moveInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* fireInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Input")
	UInputAction* reloadInput;
	
	APlayerCharacterSource();
	void MoveToDirection(FVector2D direction);
	void LookAt(FVector direction, float speed, float deltaTime);
	class UHealthComponent* GetHealthComponent() const;
	class UWeaponComponent* GetWeaponComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category= "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, Category= "Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystem;
	
	void MoveForward(const FInputActionValue& value);
	void HandleMouseInput(float deltaTime);
	void Fire();
	void Reload();
};
