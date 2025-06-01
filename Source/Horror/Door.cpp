// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "HorrorCharacter.h"

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
	if (otherActor->IsA(AHorrorCharacter::StaticClass()))
	{
		ToggleDoor(EInteractType::Player);
	}

	return Super::InteractWith_Implementation(otherActor);
}

void ADoor::ToggleDoor(EInteractType interactType)
{
	switch (interactType)
	{
	case EInteractType::ControlRoom:
		(bIsOpen) ? Close() : Open();
		bIsOpen = !bIsOpen;
		break;
	case EInteractType::Player:
		(bIsOpen) ? CloseManually() : OpenManually();
		break;
	case EInteractType::Monkey:
		break;
	}
}
