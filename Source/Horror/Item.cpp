// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Horror/HorrorCharacter.h"
#include "Horror/InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"

AItem::AItem()
{
	OuterBillboard->SetUsingAbsoluteRotation(true);
	OuterBillboard->SetUsingAbsoluteLocation(true);

	InnerBillboard->SetUsingAbsoluteRotation(true);
	InnerBillboard->SetUsingAbsoluteLocation(true);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = InteractionBox->GetComponentLocation();
	FVector BillboardLocation = ActorLocation + InteractionBillboardOffset;

	OuterBillboard->SetWorldLocation(BillboardLocation);
	InnerBillboard->SetWorldLocation(BillboardLocation);
}

void AItem::Pickup_Implementation()
{
	SetInteractability(false);
}

void AItem::Drop_Implementation()
{
	GetWorldTimerManager().SetTimer(CheckVelocityHandle, this, &AItem::CheckVelocity, 0.2f, true);
}

void AItem::CheckVelocity()
{
	if (GetVelocity().IsNearlyZero())
	{
		SetInteractability(true);
		GetWorldTimerManager().ClearTimer(CheckVelocityHandle);
	}
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
