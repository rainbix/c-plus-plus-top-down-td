#include "RangedWeapon.h"

#include "AmmoModule/ClipAmmoModule.h"
#include "Components/SkeletalMeshComponent.h"

ARangedWeapon::ARangedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	AmmoModule = CreateDefaultSubobject<UClipAmmoModule>("AmmoModule");
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (AmmoModule)
	{
		AmmoModule->OnAmmoChanged.BindUObject(this, &ARangedWeapon::HandleAmmoChanged);
	}
}

void ARangedWeapon::HandleAmmoChanged()
{
	OnAmmoChanged.Broadcast(this);
}

void ARangedWeapon::Reload() const
{
	if(!AmmoModule) return;

	AmmoModule->Reload();
}

bool ARangedWeapon::CanShoot() const
{
	if (!AmmoModule) return true;
	
	return AmmoModule->CanShoot();
}

int ARangedWeapon::GetCurrentAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetCurrentAmmo();
}

int ARangedWeapon::GetSpareAmmo() const
{
	if (!AmmoModule) return INFINITY;

	return AmmoModule->GetSpareAmmo();
}

EWeaponTypes ARangedWeapon::GetWeaponType() const
{
	return WeaponType;
}

void ARangedWeapon::OnEquip(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &GrantedHandles, this);
	}
}

void ARangedWeapon::OnUnequip(UAbilitySystemComponent* AbilitySystemComponent)
{
	GrantedHandles.TakeFromAbilitySystem(AbilitySystemComponent);
}

FVector ARangedWeapon::GetShootStartPosition() const
{
	const FTransform socketTransform = WeaponMesh->GetSocketTransform(ShootPointSocket);
	return socketTransform.GetLocation();
}

FVector ARangedWeapon::GetShootDirection() const
{
	const FTransform ownerTransform = GetOwner()->GetTransform();
	return ownerTransform.Rotator().Vector();
}

void ARangedWeapon::UpdateFiringTime()
{
	UWorld* world = GetWorld();
	check(world);
	LastFireTime = world->GetTimeSeconds();
}

float ARangedWeapon::GetTimeSinceLastFire() const
{
	return LastFireTime;
}
