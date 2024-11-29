// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamProvider.generated.h"

UENUM()
enum class ETeamType : int8
{
	None = 0,
	Player = 1,
	Enemy = 2,
};

// This class does not need to be modified.
UINTERFACE()
class UTeamProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOURCE_API ITeamProvider
{
	GENERATED_BODY()

public:
	virtual ETeamType GetTeamType() { return ETeamType::None; } 
};
