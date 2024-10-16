#include "RangedWeapon.h"

#include "AmmoModule/ClipAmmoModule.h"
#include "Components/SkeletalMeshComponent.h"

ARangedWeapon::ARangedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (AmmoModule)
	{
		AmmoModule->Initialize();
		AmmoModule->OnAmmoChanged.BindUObject(this, &ARangedWeapon::HandleAmmoChanged);
	}
}

void ARangedWeapon::HandleAmmoChanged()
{
	OnAmmoChanged.Broadcast(this);
}

bool ARangedWeapon::CheckShootCost() const
{
	if (!AmmoModule) return true;
	
	return AmmoModule->CheckShootCost();
}

void ARangedWeapon::ApplyShootCost() const
{
	if (!AmmoModule) return;

	AmmoModule->ApplyShootCost();
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
