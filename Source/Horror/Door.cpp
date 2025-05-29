// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor()
{
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Frame);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString ADoor::InteractWith_Implementation(AActor* otherActor)
{
	//ToggleDoor();
	return Super::InteractWith_Implementation(otherActor);
}

void ADoor::ToggleDoor()
{
	(bIsOpen) ? Close() : Open();

	bIsOpen = !bIsOpen;
}
