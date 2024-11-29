// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Source/TeamProvider.h"
#include "Source/AbilitySystem/SourceAbilitySystemInterface.h"
#include "PlayerCharacterSource.generated.h"

class USourceAbilitySystemComponent;

UCLASS()
class SOURCE_API APlayerCharacterSource : public ACharacter, public ISourceAbilitySystemInterface, public ITeamProvider
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float mouseRotationSpeed;

	APlayerCharacterSource();
	void MoveToDirection(FVector2D direction);
	void LookAt(FVector direction, float speed, float deltaTime);
	void SetMoveToDirection(FVector2D direction);
	void SetLookAt(FVector direction);
	class UHealthComponent* GetHealthComponent() const;
	class UWeaponComponent* GetWeaponComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual USourceAbilitySystemComponent* GetSourceAbilitySystemComponent() const override;
	virtual ETeamType GetTeamType() override { return TeamType; }

protected:
	UPROPERTY(EditDefaultsOnly)
	ETeamType TeamType = ETeamType::Player;
	
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category= "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, Category= "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere)
	USourceAbilitySystemComponent* AbilitySystem;
	
	FVector2D m_moveDirection;
	FVector m_lookDirection;
};
