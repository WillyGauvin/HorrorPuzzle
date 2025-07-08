// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "HorrorCharacter.h"
#include "Core/CustomGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

ADoor::ADoor()
{
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Frame);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(Door);

	MinimapIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapIcon"));
	MinimapIcon->SetupAttachment(Frame);

	if (ClosedSprite)
	{
		MinimapIcon->SetSprite(ClosedSprite);
	}

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
	case EInteractType::Player:
		(bIsOpen) ? Close() : Open();
		break;
	case EInteractType::Monkey:
		break;
	}
}


