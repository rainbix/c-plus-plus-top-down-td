#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroneActor.generated.h"

UCLASS()
class ADroneActor : public AActor
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Settings")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Settings")
	float AcceptanceRadius;

	GENERATED_BODY()

public:
	ADroneActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
