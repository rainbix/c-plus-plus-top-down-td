// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActiveWeaponWidget.generated.h"

class ARangedWeapon;
class UTextBlock;
class UImage;
class UTexture2D;
struct FWeaponData;
enum class EWeaponTypes : uint8;

UCLASS()
class SOURCE_API UActiveWeaponWidget : public UUserWidget
{
public:
	void InitializeWidget(const ARangedWeapon* weapon);
	void HandleWeaponAmmoChanged(const ARangedWeapon* weapon);
	void HandleWeaponChange(const ARangedWeapon* weapon);
	
private:
	
	void UpdateAmmo(int curAmmo, int maxAmmo);
	void SetWeaponType(EWeaponTypes weaponType);
	TObjectPtr<UTexture2D> GetWeaponIcon(EWeaponTypes weaponType);

	UPROPERTY(EditDefaultsOnly, Category = "Assets")
	TMap<EWeaponTypes, TObjectPtr<UTexture2D>> weaponTypeTexturesMap;
	
	UPROPERTY(EditDefaultsOnly, Category="Assets")
	TObjectPtr<UTexture2D> errorTexture;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> weaponTypeIcon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> ammoAmountIcon;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ammoCountText;
	
	GENERATED_BODY()
};
