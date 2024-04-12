#pragma once

#include "CoreMinimal.h"
#include "DamageInformation.generated.h"

USTRUCT(BlueprintType)
struct FDamageInformation
{
	GENERATED_BODY();
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;

	FDamageInformation();
	explicit FDamageInformation(float damageValue);
};

inline FDamageInformation::FDamageInformation(): Value(0)
{
}

inline FDamageInformation::FDamageInformation(const float damageValue): Value(damageValue)
{
}

