#pragma once

#include "CoreMinimal.h"
#include "TowerActor.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

struct FGameplayEffectSpecHandle;

UCLASS(Abstract)
class AProjectile : public AActor
{
	GENERATED_BODY()
    
public:    
	AProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;

	TArray<FGameplayEffectSpecHandle> EffectsToApply;
	float Range;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};