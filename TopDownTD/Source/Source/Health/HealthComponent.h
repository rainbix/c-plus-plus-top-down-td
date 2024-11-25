#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
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
	FOnHealthChange OnCurrentHealthChangeDelegate;
	FOnHealthChange OnMaxHealthChangeDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDie, AActor*)
	FOnDie OnDieDelegate;

#pragma endregion 

protected:
	UPROPERTY()
	const class UHealthAttributeSet* HealthSet;

	bool IsInitialized;

	void HandleCurrentHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;
	virtual void BeginPlay() override;
	virtual void OnDeath();
};
