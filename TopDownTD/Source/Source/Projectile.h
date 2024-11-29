#pragma once

#include "CoreMinimal.h"
#include "TeamProvider.h"
#include "TowerActor.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

struct FGameplayEffectSpecHandle;

UCLASS(Abstract)
class AProjectile : public AActor, public ITeamProvider
{
	GENERATED_BODY()
    
public:    
	AProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, signed int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	ETeamType TeamType = ETeamType::None;;
	
public:    
	virtual void Tick(float DeltaTime) override;
	virtual ETeamType GetTeamType() override { return TeamType; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;

	TArray<FGameplayEffectSpecHandle> EffectsToApply;
	float Range;
};