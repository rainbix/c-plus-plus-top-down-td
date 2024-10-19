// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerBuildController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOURCE_API UTowerBuildController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTowerBuildController();

protected:
	virtual void BeginPlay() override;

private:
	void BuildInputHandler();
};
