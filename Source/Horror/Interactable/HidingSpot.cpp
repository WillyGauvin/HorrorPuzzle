// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "HidingSpot.h"
#include "Horror/Characters/HorrorCharacter.h"

//Engine Includes
#include "Components/BoxComponent.h"

AHidingSpot::AHidingSpot()
{
	HidingSpotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HidingSpotMesh"));
	HidingSpotMesh->SetupAttachment(RootComponent);

	InteractionBox->SetupAttachment(HidingSpotMesh);
}

void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();
}

void AHidingSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AHidingSpot::InteractWith_Implementation(AActor* otherActor)
{
	if (AHorrorCharacter* Character = Cast<AHorrorCharacter>(otherActor))
	{
		Character->InteractWithHiding(this);
	}

	return Super::InteractWith_Implementation(otherActor);
}