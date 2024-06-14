// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveWeaponWidget.h"
#include "FWeaponData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UActiveWeaponWidget::InitializeWidget(const FWeaponData* weaponData)
{
	UpdateAmmo(weaponData->curAmmo, weaponData->maxAmmo);
	SetWeaponType(weaponData->weaponType);
}

void UActiveWeaponWidget::UpdateAmmo(int curAmmo, int maxAmmo)
{
	if (ammoCountText)
	{
		const FString ammoStr = FString::Printf(TEXT("%d / %d"), curAmmo, maxAmmo);
		ammoCountText->SetText(FText::FromString(ammoStr));
	}
}

void UActiveWeaponWidget::SetWeaponType(EWeaponTypes weaponType)
{
	if (weaponTypeIcon)
	{
		const auto weaponIcon = GetWeaponIcon(weaponType);
		const auto brushImageSize = weaponTypeIcon->GetBrush().ImageSize;
		
		FSlateBrush Brush;
		Brush.SetResourceObject(weaponIcon);
		Brush.ImageSize = brushImageSize;
		
		weaponTypeIcon->SetBrush(Brush);
	}
}

TObjectPtr<UTexture2D> UActiveWeaponWidget::GetWeaponIcon(EWeaponTypes weaponType)
{
	if (const TObjectPtr<UTexture2D>* ptrToIconPtr = weaponTypeTexturesMap.Find(weaponType))
		return *ptrToIconPtr;	

	return errorTexture;
}
