#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponShootModule.generated.h"

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UWeaponShootModule : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponShootModule();

	virtual void Shoot(FVector StartPosition, FVector Direction)	{	}
};