// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfiniteAmmoModule.h"
#include "ClipAmmoModule.generated.h"


UCLASS(DefaultToInstanced, EditInlineNew, DisplayName="Clip ammo")
class SOURCE_API UClipAmmoModule : public UInfiniteAmmoModule
{
	GENERATED_BODY()

public:
	UClipAmmoModule()
	{
	}

protected:
	UPROPERTY(EditAnywhere, Category="Parameters")
	int MaxClipAmmo = 10;
	
	UPROPERTY(EditAnywhere, Category="Parameters")
	int MaxSpareAmmo = 50;
	
	UPROPERTY(EditAnywhere, Category="Parameters")
	int AmmoPerShot = 1;
	
	UPROPERTY(EditAnywhere, Category="Parameters")
	float ReloadDuration = 2;
	
	float ReloadStartTime = 0;	
	int CurrentClipAmmo = 10;
	int SpareAmmoLeft = 50;

public:	
	virtual void Initialize() override;
	virtual bool CheckShootCost() const override;
	virtual void ApplyShootCost() override;
	virtual void AddAmmo(int Value);
	virtual int GetCurrentAmmo() const override;
	virtual int GetSpareAmmo() const override;
	virtual bool CanReload() const override;
	virtual void ApplyReload() override;
};
