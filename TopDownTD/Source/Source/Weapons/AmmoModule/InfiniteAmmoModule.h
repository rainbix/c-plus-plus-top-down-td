#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InfiniteAmmoModule.generated.h"

UCLASS(DefaultToInstanced, EditInlineNew, DisplayName="Infinite ammo")
class SOURCE_API UInfiniteAmmoModule : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE(FOnAmmoChanged)
	FOnAmmoChanged OnAmmoChanged;
	
	UInfiniteAmmoModule() {}

	virtual void Initialize() {}
	virtual bool CheckShootCost() const {return true;}
	virtual void ApplyShootCost() {}
	virtual int GetCurrentAmmo() const {return INFINITY;}
	virtual int GetSpareAmmo() const {return INFINITY;}
};
