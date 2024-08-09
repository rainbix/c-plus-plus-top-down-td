#include "WeaponComponent.h"

#include "EnhancedInputComponent.h"
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

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent))
	{
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Fire);
	}
}

void UWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;

	ACharacter* character = Cast<ACharacter>(GetOwner());
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
	
	if(!CurrentWeapon) return;
	
	FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(character->GetMesh(), attachmentRules, WeaponSocketName);
}


