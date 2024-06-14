// Fill out your copyright notice in the Description page of Project Settings.


#include "HudTestWidget.h"

void UHudTestWidget::IncreaseHealth(int amount)
{
	CurHealth = FMath::Clamp(CurHealth + amount, 0, MaxHealth);
	OnHealthIncreasedDelegate.Broadcast(CurHealth);
}

void UHudTestWidget::DecreaseHealth(int amount)
{
	CurHealth = FMath::Clamp(CurHealth - amount, 0, MaxHealth);
	OnHealthDecreasedDelegate.Broadcast(CurHealth);
}

void UHudTestWidget::Shoot()
{
	OnShootDelegate.Broadcast();
}
