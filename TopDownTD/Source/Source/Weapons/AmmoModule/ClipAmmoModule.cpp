#include "ClipAmmoModule.h"
#include "Source/Source.h"

UClipAmmoModule::UClipAmmoModule()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxClipAmmo = 10;
	CurrentClipAmmo = MaxClipAmmo;
	ReloadDuration = 0;
	ReloadStartTime = 0;
	IsReloading = false;
}

// Called when the game starts
void UClipAmmoModule::BeginPlay()
{
	Super::BeginPlay();

	CurrentClipAmmo = MaxClipAmmo;
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
		CurrentClipAmmo = MaxClipAmmo;
		UE_LOG(LogFWeapon, Display, TEXT("Reload finished)"))
	}
}

void UClipAmmoModule::Reload()
{
	if (IsReloading) return;
	if(CurrentClipAmmo >= MaxClipAmmo) return;
	if (!GetWorld()) return;

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

