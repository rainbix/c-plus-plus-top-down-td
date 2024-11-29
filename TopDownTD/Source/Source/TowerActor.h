#pragma once

#include "CoreMinimal.h"
#include "TeamProvider.h"
#include "AbilitySystem/SourceAbilitySystemInterface.h"
#include "AbilitySystem/SourceAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "TowerActor.generated.h"

class UAbilitySet;

UCLASS()
class ATowerActor : public AActor, public ISourceAbilitySystemInterface, public ITeamProvider
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
	ETeamType TeamType;

	virtual void BeginPlay() override;
	void FindTarget();
	bool IsValidTarget(ACharacter* Character, float& DistanceSqr);
	
public:
	virtual void Tick(float DeltaTime) override;
	USkeletalMeshComponent* GetSkeletalMesh() const { return MeshComponent; }
	virtual USourceAbilitySystemComponent* GetSourceAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent; }
	AActor* GetTarget() const;
	float GetRange() const { return Range; }
	virtual ETeamType GetTeamType() override { return TeamType; }
};