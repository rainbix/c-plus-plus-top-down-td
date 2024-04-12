// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Units/DamageableActor.h"
#include "Units/HealthComponent.h"
#include "SourceCharacter.generated.h"

UCLASS(Blueprintable)
class ASourceCharacter : public ACharacter, public IDamageableActor
{
	GENERATED_BODY()

public:
	
	ASourceCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void ReceiveDamage_Implementation(FDamageInformation DamageInfo) override;
	virtual bool IsDead_Implementation() override;
	virtual int GetCurrentHealth_Implementation() override;
	virtual int GetMaxHealth_Implementation() override;
	virtual void DoShit() override;
	virtual void Something_Implementation() override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category= "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	
	float TimeSinceLastDamage;
	
};

