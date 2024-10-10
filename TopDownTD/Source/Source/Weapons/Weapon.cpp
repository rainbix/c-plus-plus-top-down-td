#include "Weapon.h"

#include "AbilitySystemComponent.h"
#include "AmmoModule/ClipAmmoModule.h"
#include "Components/SkeletalMeshComponent.h"
#include "Source/Source.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	AmmoModule = CreateDefaultSubobject<UClipAmmoModule>("AmmoModule");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (AmmoModule)
	{
		AmmoModule->OnAmmoChanged.BindUObject(this, &AWeapon::HandleAmmoChanged);
	}
}

void AWeapon::HandleAmmoChanged()
{
	OnAmmoChanged.Broadcast(this);
}

void AWeapon::Fire()
{
	if(!GetWorld()) return;
	if(!CanShoot()) return;
	if(!OwnerAbilitySystem) return;

	// double currentTime = GetWorld()->GetTime().GetWorldTimeSeconds();
	// if (currentTime - LastBulletShotTime < FireRate)
	// {
	// 	return;
	// }
	//
	// LastBulletShotTime = currentTime;
	if(!OwnerAbilitySystem->TryActivateAbility(FireAbilitySpec))
	{
		return;
	}

	UE_LOG(LogFWeapon, Display, TEXT("Fire)"))
	
	if (AmmoModule)
	{
		AmmoModule->OnShot();
	}

	OnAmmoChanged.Broadcast(this);
}

void AWeapon::Reload() const
{
	if(!AmmoModule) return;

	AmmoModule->Reload();
}

bool AWeapon::CanShoot() const
{
	if (!AmmoModule) return true;
	
	return AmmoModule->CanShoot();
}

int AWeapon::GetCurrentAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetCurrentAmmo();
}

int AWeapon::GetSpareAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetSpareAmmo();
}

EWeaponTypes AWeapon::GetWeaponType() const
{
	return WeaponType;
}

void AWeapon::OnEquip(UAbilitySystemComponent* AbilitySystemComponent)
{
	FireAbilitySpec = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireAbility, 1, INDEX_NONE, this));
	OwnerAbilitySystem = AbilitySystemComponent;
}

void AWeapon::OnUnequip(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (FireAbilitySpec.IsValid())
	{
		AbilitySystemComponent->ClearAbility(FireAbilitySpec);
		OwnerAbilitySystem = nullptr;
	}
}

FVector AWeapon::GetShootStartPosition() const
{
	const FTransform socketTransform = WeaponMesh->GetSocketTransform(ShootPointSocket);
	return socketTransform.GetLocation();
}

FVector AWeapon::GetShootDirection()
{
	const FTransform ownerTransform = GetOwner()->GetTransform();
	return ownerTransform.Rotator().Vector();
}
