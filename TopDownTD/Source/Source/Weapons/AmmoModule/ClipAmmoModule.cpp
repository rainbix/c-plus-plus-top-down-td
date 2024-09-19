#include "ClipAmmoModule.h"
#include "Source/Source.h"

UClipAmmoModule::UClipAmmoModule()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentClipAmmo = MaxClipAmmo;
	SpareAmmoLeft = MaxSpareAmmo;
	ReloadStartTime = 0;
	IsReloading = false;
}

// Called when the game starts
void UClipAmmoModule::BeginPlay()
{
	Super::BeginPlay();

	CurrentClipAmmo = MaxClipAmmo;
	SpareAmmoLeft = MaxSpareAmmo;
}

// Called every frame
void UClipAmmoModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetWorld()) return;
	if (!IsReloading) return;

	float currentTime = GetWorld()->GetTimeSeconds();

	if (currentTime - ReloadStartTime > ReloadDuration)
	{
		IsReloading = false;
		int ammoToAdd = FMath::Min(MaxClipAmmo - CurrentClipAmmo, SpareAmmoLeft);
		CurrentClipAmmo += ammoToAdd;
		SpareAmmoLeft -= ammoToAdd;
		UE_LOG(LogFWeapon, Display, TEXT("Reload finished: SpareAmmoLeft [%i])"), SpareAmmoLeft)
	}
}

void UClipAmmoModule::Reload()
{
	if (IsReloading) return;
	if (CurrentClipAmmo >= MaxClipAmmo) return;
	if (!GetWorld()) return;
	if (SpareAmmoLeft <= 0) return;

	IsReloading = true;
	ReloadStartTime = GetWorld()->GetTimeSeconds();
	UE_LOG(LogFWeapon, Display, TEXT("Reload started)"))
}

bool UClipAmmoModule::CanShoot()
{
	return !IsReloading && CurrentClipAmmo > 0;
}

void UClipAmmoModule::OnShot()
{
	if (CurrentClipAmmo > 0)
	{
		CurrentClipAmmo--;
		UE_LOG(LogFWeapon, Display, TEXT("Ammo left %i"), CurrentClipAmmo);
	}
}

void UClipAmmoModule::AddAmmo(int Value)
{
	SpareAmmoLeft = FMath::Clamp(SpareAmmoLeft + Value, 0, MaxSpareAmmo);

	UE_LOG(LogFWeapon, Display, TEXT("Add ammo: SpareAmmoLeft [%i])"), SpareAmmoLeft)
}

int UClipAmmoModule::GetCurrentAmmo() const
{
	return CurrentClipAmmo;
}

int UClipAmmoModule::GetSpareAmmo() const
{
	return SpareAmmoLeft;
}
