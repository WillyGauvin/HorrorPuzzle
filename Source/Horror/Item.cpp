// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Horror/HorrorCharacter.h"
#include "Horror/InventoryComponent.h"
#include "Components/WidgetComponent.h"

AItem::AItem()
{
}

void AItem::StartLookAt_Implementation(APlayerController* PlayerController)
{
	if (ActiveInteractionWidget)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "TakenOff");
		ActiveInteractionWidget->RemoveFromParent();
		ActiveInteractionWidget = nullptr;
	}

	if (InteractionWidgetClass && PlayerController)
	{
		if (AHorrorCharacter* Character = Cast<AHorrorCharacter>(PlayerController->GetPawn()))
		{
			if (Character->InventoryComponent)
			{
				if (Character->InventoryComponent->IsRoomForItem(GetClass()))
				{
					// Delegate UI creation to the controller
					ActiveInteractionWidget = CreateWidget<UUserWidget>(PlayerController, CanPickupWidgetClass);
				}
				else
				{
					// Delegate UI creation to the controller
					ActiveInteractionWidget = CreateWidget<UUserWidget>(PlayerController, CannotPickupWidgetClass);
				}
			}
		}

		if (ActiveInteractionWidget)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PutOn");
			ActiveInteractionWidget->AddToViewport();
		}
	}
}

FString AItem::InteractWith_Implementation(AActor* otherActor)
{
	if (AHorrorCharacter* Character = Cast<AHorrorCharacter>(otherActor))
	{
		if (Character->InventoryComponent->AddItem(GetClass()))
		{
			Destroy();
		}
	}
	return FString();
}
