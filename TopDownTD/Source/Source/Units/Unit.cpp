#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
}

void AUnit::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FDamageInformation dmgInfo(10);

	ReceiveDamage_Implementation(dmgInfo);
}

void AUnit::ReceiveDamage_Implementation(FDamageInformation DamageInfo)
{
	HealthComponent->ReceiveDamage(DamageInfo);

	if(IsDead_Implementation())
	{
		Destroy();
	}
}

bool AUnit::IsDead_Implementation() const
{
	return HealthComponent->IsDead();
}

int AUnit::GetCurrentHealth_Implementation() const
{
	return HealthComponent->GetCurrentHealth();
}

int AUnit::GetMaxHealth_Implementation() const
{
	return HealthComponent->GetMaxHealth();
}
