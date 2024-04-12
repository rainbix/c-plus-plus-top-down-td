// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibraryA.generated.h"

/**
 * 
 */
UCLASS()
class SOURCE_API UMyBlueprintFunctionLibraryA : public UBlueprintFunctionLibrary
{
public:

	UFUNCTION(BlueprintCallable)
	static FString GetPointlessMessage();

private:
	GENERATED_BODY()
	
};
