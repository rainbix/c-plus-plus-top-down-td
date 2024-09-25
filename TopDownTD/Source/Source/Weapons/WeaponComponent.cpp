#include "WeaponComponent.h"
#include "Weapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::Fire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->Fire();
}

void UWeaponComponent::Reload()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->Reload();
}

AWeapon* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;

	//todo: ACharacter cast makes it impossible to use weapon by other pawns
	ACharacter* character = Cast<ACharacter>(GetOwner());
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
	
	if(!CurrentWeapon) return;
	
	FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(character->GetMesh(), attachmentRules, WeaponSocketName);
	CurrentWeapon->SetOwner(character);
	CurrentWeapon->SetInstigator(character);
	SubscribeOnWeapon();
	OnWeaponChanged.Broadcast(CurrentWeapon);
}

void UWeaponComponent::SubscribeOnWeapon()
{
	CurrentWeapon->OnAmmoChanged.AddUObject(this, &UWeaponComponent::HandleWeaponAmmoChanged);
}

void UWeaponComponent::UnsubscribeOnWeapon()
{
	if (!CurrentWeapon) return;
	
	CurrentWeapon->OnAmmoChanged.RemoveAll(this);
}

void UWeaponComponent::HandleWeaponAmmoChanged(AWeapon* weapon) const
{
	OnWeaponAmmoChange.Broadcast(weapon);
}


