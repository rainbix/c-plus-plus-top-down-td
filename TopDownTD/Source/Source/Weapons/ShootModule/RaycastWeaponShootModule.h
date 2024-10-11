#pragma once

#include "CoreMinimal.h"
#include "WeaponShootModule.h"
#include "Components/ActorComponent.h"
#include "RaycastWeaponShootModule.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API URaycastWeaponShootModule : public UWeaponShootModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parameters")
	float TraceMaxDistance = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float DamageValue = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TSubclassOf<UDamageType> DamageTypeClass;

public:
	URaycastWeaponShootModule();

	virtual void Shoot(FVector StartPosition, FVector Direction) override;
};