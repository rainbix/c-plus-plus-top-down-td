#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SourceAbilitySystemInterface.h"
#include "AbilitySystem/SourceAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "TowerActor.generated.h"

class UAbilitySet;

UCLASS()
class ATowerActor : public AActor, public ISourceAbilitySystemInterface
{
	GENERATED_BODY()
public:    
	ATowerActor();

protected:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Settings")
	float Range;

	UPROPERTY(EditDefaultsOnly, Category= "Tower Settings")
	USourceAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Settings")
	UAbilitySet* AbilitySet;
	
	FTimerHandle FireRateTimerHandle;
	ACharacter* MainCharacter;
	bool HadTarget;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	USkeletalMeshComponent* GetSkeletalMesh() const { return MeshComponent; }
	virtual USourceAbilitySystemComponent* GetSourceAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent; }
	AActor* GetTarget() const;
	float GetRange() const { return Range; }
};