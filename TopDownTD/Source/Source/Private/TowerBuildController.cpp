// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBuildController.h"

#include "MyPlayerController.h"
#include "Source/Tools/GeneralPurposeUtils.h"

// Sets default values for this component's properties
UTowerBuildController::UTowerBuildController()
{

}


void UTowerBuildController::BeginPlay()
{
	Super::BeginPlay();
	
	if (const auto playerController = Cast<AMyPlayerController>(GetOwner()))
	{
		playerController->OnBuildInputDelegate.AddUObject(this, &UTowerBuildController::BuildInputHandler);
	}
}

void UTowerBuildController::BuildInputHandler()
{
	GeneralPurposeUtils::DisplayScreenMessage("Process build input");
}

