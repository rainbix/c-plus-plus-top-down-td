// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoModule.h"
#include "ClipAmmoModule.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOURCE_API UClipAmmoModule : public UAmmoModule
{
	GENERATED_BODY()

public:
	UClipAmmoModule();

protected:
	UPROPERTY(EditAnywhere, Category="Parameters")
	int MaxClipAmmo = 10;
	int CurrentClipAmmo;

	UPROPERTY(EditAnywhere, Category="Parameters")
	int MaxSpareAmmo = 50;
	int SpareAmmoLeft;

	UPROPERTY(EditAnywhere, Category="Parameters")
	float ReloadDuration = 2;
	float ReloadStartTime;
	bool IsReloading;
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Reload() override;
	virtual bool CanShoot() override;
	virtual void OnShot() override;
	virtual void AddAmmo(int Value);
};
