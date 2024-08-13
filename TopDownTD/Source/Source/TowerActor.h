#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"  // Додайте цей рядок
#include "TowerActor.generated.h"

UCLASS()
class ATowerActor : public AActor
{
	GENERATED_BODY()
public:    
	ATowerActor();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	void Fire();

	FTimerHandle FireRateTimerHandle;
	ACharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Settings")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Settings")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Settings")
	TSubclassOf<AProjectile> ProjectileClass;
};