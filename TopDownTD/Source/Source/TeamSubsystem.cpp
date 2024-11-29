// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSubsystem.h"

#include "TeamProvider.h"

bool UTeamSubsystem::IsSameTeam(UObject* ObjectA, UObject* ObjectB)
{
	ITeamProvider* ObjectATeamProvider = Cast<ITeamProvider>(ObjectA);

	ObjectA = nullptr;

	if (!ObjectATeamProvider)
	{
		return false;
	}

	ITeamProvider* ObjectBTeamProvider = Cast<ITeamProvider>(ObjectB);

	if (!ObjectBTeamProvider)
	{
		return false;
	}

	const ETeamType ObjectATeamType = ObjectATeamProvider->GetTeamType();
	const ETeamType ObjectBTeamType = ObjectBTeamProvider->GetTeamType();
	
	if (ObjectATeamType == ETeamType::None || ObjectBTeamType == ETeamType::None)
	{
		return false;
	}

	return ObjectATeamType == ObjectBTeamType;
}
