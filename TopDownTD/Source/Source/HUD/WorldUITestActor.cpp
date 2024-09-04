// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldUITestActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWorldUITestActor::AWorldUITestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 33;
}

// Called when the game starts or when spawned
void AWorldUITestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldUITestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldUITestActor::ApplyCustomDamage()
{
	UGameplayStatics::ApplyDamage(this, Damage, GetWorld()->GetFirstPlayerController(), GetOwner(), DamageType);
}

