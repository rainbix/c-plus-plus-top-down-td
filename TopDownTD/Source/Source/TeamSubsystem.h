// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SOURCE_API UTeamSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static bool IsSameTeam(UObject* ObjectA, UObject* ObjectB);
};
