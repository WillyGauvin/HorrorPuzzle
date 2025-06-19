// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "HorrorCharacter.h"
#include "Core/CustomGameMode.h"
#include "Kismet/KismetMathLibrary.h"

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

bool ADoor::TryBreakDoor()
{
	if (bIsBroken)
	{
		return true;
	}

	int DoorsOpenedWithoutBreak = GetWorld()->GetAuthGameMode<ACustomGameMode>()->GetDoorsOpenedWithoutBreak();

	int ChanceToBreak = int(FMath::Pow(float(DoorsOpenedWithoutBreak), 2.0f) * 3.5f);

	int randInt = FMath::RandRange(1, 100);

	GEngine->AddOnScreenDebugMessage(
		-1,                      // Unique key (use -1 for new message)
		1.0f,                    // Duration in seconds
		FColor::Yellow,          // Text color
		FString::Printf(TEXT("DoorOpenCount: %d"), GetWorld()->GetAuthGameMode<ACustomGameMode>()->GetDoorsOpenedWithoutBreak())
	);

	GEngine->AddOnScreenDebugMessage(
		-1,                      // Unique key (use -1 for new message)
		1.0f,                    // Duration in seconds
		FColor::Yellow,          // Text color
		FString::Printf(TEXT("ChanceToBreak: %d"), ChanceToBreak)
	);

	if (randInt <= ChanceToBreak) // Door is broken
	{
		BreakDoor();
		GetWorld()->GetAuthGameMode<ACustomGameMode>()->ResetDoorsOpenedWithoutBreak();
	}
	else
	{
		GetWorld()->GetAuthGameMode<ACustomGameMode>()->AddDoorsOpenedWithoutBreak();
	}

	return bIsBroken;
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
		if (!bIsBroken)
		{
			if (bIsOpen)
			{
				Close();
			}
			else
			{
				if (!TryBreakDoor())
				{
					Open();
				}
			}
		}
		break;
	case EInteractType::Player:
		if (bIsBroken)
		{
			FixDoor();
		}
		else
		{
			(bIsOpen) ? CloseManually() : OpenManually();	
		}
		break;
	case EInteractType::Monkey:
		break;
	}
}
