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
	
	UPROPERTY(EditDefaultsOnly, Category = "Tower Settings")
	float TargetSearchDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category= "Tower Settings")
	USourceAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Settings")
	UAbilitySet* AbilitySet;
	
	FTimerHandle SearchTargetTimerHandle;
	UPROPERTY()
	ACharacter* TargetCharacter;
	bool HadTarget;

	virtual void BeginPlay() override;
	void FindTarget();
	bool IsValidTarget(const ACharacter* Character, float& DistanceSqr) const;
	
public:
	virtual void Tick(float DeltaTime) override;
	USkeletalMeshComponent* GetSkeletalMesh() const { return MeshComponent; }
	virtual USourceAbilitySystemComponent* GetSourceAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent; }
	AActor* GetTarget() const;
	float GetRange() const { return Range; }
};