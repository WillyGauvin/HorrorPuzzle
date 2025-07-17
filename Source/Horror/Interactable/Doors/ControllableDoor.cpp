// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "ControllableDoor.h"
#include "Horror/Core/CustomGameMode.h"

//Engine Includes
#include "Components/ChildActorComponent.h"


AControllableDoor::AControllableDoor()
{
	DoorWidgetLocation = CreateDefaultSubobject<UChildActorComponent>(TEXT("DoorWidgetLocation"));
	DoorWidgetLocation->SetupAttachment(Frame);
}

bool AControllableDoor::TryBreakDoor()
{
	if (bIsBroken)
	{
		return true;
	}

	int DoorsOpenedWithoutBreak = GetWorld()->GetAuthGameMode<ACustomGameMode>()->GetDoorsOpenedWithoutBreak();

	int ChanceToBreak = int(FMath::Pow(float(DoorsOpenedWithoutBreak), 2.0f) * 3.5f);

	int randInt = FMath::RandRange(1, 100);

	//Debug for chance doors have of breaking
	//GEngine->AddOnScreenDebugMessage(
	//	-1,                      // Unique key (use -1 for new message)
	//	1.0f,                    // Duration in seconds
	//	FColor::Yellow,          // Text color
	//	FString::Printf(TEXT("DoorOpenCount: %d"), GetWorld()->GetAuthGameMode<ACustomGameMode>()->GetDoorsOpenedWithoutBreak())
	//);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,                      // Unique key (use -1 for new message)
	//	1.0f,                    // Duration in seconds
	//	FColor::Yellow,          // Text color
	//	FString::Printf(TEXT("ChanceToBreak: %d"), ChanceToBreak)
	//);

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

FVector AControllableDoor::GetDoorLocation()
{
	return Door->GetComponentTransform().GetLocation();
}

void AControllableDoor::ToggleDoor(EInteractType interactType)
{
	switch (interactType)
	{
	case EInteractType::ControlRoom:
		if (!bIsBroken)
		{
			if (bIsOpen)
			{
				Close();
				InteractionWidgetClass = CloseDoorWidgetClass;
			}
			else
			{
				if (!TryBreakDoor())
				{
					Open();
					InteractionWidgetClass = OpenDoorWidgetClass;
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
			if (bIsOpen)
			{
				InteractionWidgetClass = OpenDoorWidgetClass;
				CloseManually();
			}
			else
			{
				OpenManually();
			}
			ReloadWidget();
		}
		break;
	case EInteractType::Monkey:
		break;
	}
}