// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOURCE_API AGameplayHUD : public AHUD
{
public:
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UMinLayoutBase> MinimalLayoutClass = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:

	//UPROPERTY()
	//TObjectPtr<UMinLayoutBase> MinimalWidget = nullptr;
	
	//UPROPERTY()
	//TObjectPtr<AMyCppCharacter> PlayerCharacter = nullptr;
	
	GENERATED_BODY()
	
};
