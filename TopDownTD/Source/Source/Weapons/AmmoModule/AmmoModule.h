#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoModule.generated.h"

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UAmmoModule : public UActorComponent
{
	GENERATED_BODY()

public:
	UAmmoModule();

	virtual void Reload()	{	}
	virtual bool CanShoot() {return true;}
	virtual void OnShot() {}
};
