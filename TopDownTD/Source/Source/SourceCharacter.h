// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SourceCharacter.generated.h"

UCLASS(Blueprintable)
class ASourceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASourceCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	TSubclassOf<class AWeapon> DefaultWeaponClass;
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	FName WeaponSocketName;
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

	void SpawnWeapon();
	// UPROPERTY(EditAnywhere, Category="Weapon", meta=(AllowPrivateAccess = "true"))
	// TSubclassOf<AWeapon> StartingWeapon;
	//
	// AWeapon* CurrentWeapon;
};

