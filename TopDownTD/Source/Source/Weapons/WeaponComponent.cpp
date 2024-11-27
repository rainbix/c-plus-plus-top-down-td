#include "WeaponComponent.h"
#include "AbilitySystemInterface.h"
#include "RangedWeapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	isInitialized = false;
}

void UWeaponComponent::Reload()
{
	if (!CurrentWeapon) return;
}

bool UWeaponComponent::GetIsInitialized()
{
	return isInitialized;
}

ARangedWeapon* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerAbilitySystem = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();
	check(OwnerAbilitySystem);
	SpawnWeapon();
	
	isInitialized = true;
	OnComponentInitializeDelegate.Broadcast(GetCurrentWeapon());
}

void UWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;

	//todo: ACharacter cast makes it impossible to use weapon by other pawns
	ACharacter* character = Cast<ACharacter>(GetOwner());
	CurrentWeapon = GetWorld()->SpawnActor<ARangedWeapon>(DefaultWeaponClass);
	
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
	CurrentWeapon->OnEquip(OwnerAbilitySystem);
}

void UWeaponComponent::UnsubscribeOnWeapon()
{
	if (!CurrentWeapon) return;
	
	CurrentWeapon->OnAmmoChanged.RemoveAll(this);
	CurrentWeapon->OnUnequip(OwnerAbilitySystem);
}

void UWeaponComponent::HandleWeaponAmmoChanged(ARangedWeapon* weapon) const
{
	OnWeaponAmmoChange.Broadcast(weapon);
}


