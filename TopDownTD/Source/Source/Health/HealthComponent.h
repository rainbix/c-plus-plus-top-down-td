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

	bool GetIsInitialized();

#pragma region Delegates

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnComponentInitialze, int, int)
	FOnComponentInitialze OnComponentInitializeDelegate;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, int)
	FOnHealthChange OnHealthChangeDelegate;

	DECLARE_MULTICAST_DELEGATE(FOnDie)
	FOnDie OnDieDelegate;

#pragma endregion 

protected:

	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth;

	float CurrentHealth;
	bool IsInitialized;

	virtual void BeginPlay() override;
	virtual void OnDeath();
	UFUNCTION()
	virtual void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
