#include "Weapon.h"

#include "AmmoModule/ClipAmmoModule.h"
#include "Components/SkeletalMeshComponent.h"

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
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &GrantedHandles, this);
	}
}

void AWeapon::OnUnequip(UAbilitySystemComponent* AbilitySystemComponent)
{
	GrantedHandles.TakeFromAbilitySystem(AbilitySystemComponent);
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
