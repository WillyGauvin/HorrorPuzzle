// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorController.h"
#include "Door.h"

ADoorController::ADoorController()
{
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
}

FString ADoorController::InteractWith_Implementation(AActor* otherActor)
{
	if (LinkedDoor)
	{
		LinkedDoor->ToggleDoor(EInteractType::ControlRoom);
	}

	return Super::InteractWith_Implementation(otherActor);
}
