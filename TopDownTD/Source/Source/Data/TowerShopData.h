#pragma once

#include "CoreMinimal.h"
#include "TowerShopData.generated.h"

class ATowerActor;

USTRUCT(BlueprintType)
struct SOURCE_API FTowerShopData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText TowerName;

	UPROPERTY(EditDefaultsOnly)
	int BuildTime;

	UPROPERTY(EditDefaultsOnly)
	int Cost;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> TowerIcon;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<ATowerActor> TowerClass;
};
