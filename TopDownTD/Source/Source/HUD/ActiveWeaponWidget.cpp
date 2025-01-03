// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveWeaponWidget.h"
#include "FWeaponData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Source/Weapons/RangedWeapon.h"

void UActiveWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReloadBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UActiveWeaponWidget::InitializeWidget(const ARangedWeapon* weapon)
{
	UpdateAmmo(weapon->GetCurrentAmmo(), weapon->GetSpareAmmo());
	SetWeaponType(weapon->GetWeaponType());
}

void UActiveWeaponWidget::HandleWeaponAmmoChanged(const ARangedWeapon* weapon)
{
	UpdateAmmo(weapon->GetCurrentAmmo(), weapon->GetSpareAmmo());
}

void UActiveWeaponWidget::HandleWeaponChange(const ARangedWeapon* weapon)
{
	UpdateAmmo(weapon->GetCurrentAmmo(), weapon->GetSpareAmmo());
	SetWeaponType(weapon->GetWeaponType());
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

void UActiveWeaponWidget::StartReload()
{
	if (!AmmoBox || !ReloadBox)
		return;

	AmmoBox->SetVisibility(ESlateVisibility::Collapsed);
	ReloadBox->SetVisibility(ESlateVisibility::Visible);
}

void UActiveWeaponWidget::FinishReload()
{
	if (!AmmoBox || !ReloadBox)
		return;

	AmmoBox->SetVisibility(ESlateVisibility::Visible);
	ReloadBox->SetVisibility(ESlateVisibility::Collapsed);
}
