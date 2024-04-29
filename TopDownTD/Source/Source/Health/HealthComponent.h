#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),
	Blueprintable)
class SOURCE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UHealthComponent();

	virtual bool IsDead();
	virtual int GetCurrentHealth();
	virtual int GetMaxHealth();

protected:

	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth;

	float CurrentHealth;

	virtual void BeginPlay() override;
	virtual void OnDeath();
	UFUNCTION()
	virtual void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
