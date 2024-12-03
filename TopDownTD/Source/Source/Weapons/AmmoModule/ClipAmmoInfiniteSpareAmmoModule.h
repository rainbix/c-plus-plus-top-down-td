// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfiniteAmmoModule.h"
#include "UObject/Object.h"
#include "ClipAmmoInfiniteSpareAmmoModule.generated.h"

/**
 * 
 */
UCLASS()
class SOURCE_API UClipAmmoInfiniteSpareAmmoModule : public UInfiniteAmmoModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Parameters")
	int MaxClipAmmo = 10;

	int CurrentClipAmmo;
public:
	virtual void Initialize() override;
	virtual bool CheckShootCost() const override;
	virtual void ApplyShootCost() override;
	virtual int GetCurrentAmmo() const override;
	virtual int GetSpareAmmo() const override;
	virtual bool CanReload() const override;
	virtual void ApplyReload() override;
};
