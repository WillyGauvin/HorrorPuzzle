// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/WidgetComponent.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	StopLookAt();
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AInteractable::InteractWith_Implementation(AActor* otherActor)
{
	return ID;
}

void AInteractable::StartLookAt_Implementation(APlayerController* PlayerController)
{
	if (ActiveInteractionWidget)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "TakenOff");
		ActiveInteractionWidget->RemoveFromParent();
		ActiveInteractionWidget = nullptr;
	}

	if (InteractionWidgetClass && PlayerController)
	{
		// Delegate UI creation to the controller
		ActiveInteractionWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);

		if (ActiveInteractionWidget)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PutOn");
			ActiveInteractionWidget->AddToViewport();
		}
	}
}

void AInteractable::StopLookAt_Implementation()
{
	if (ActiveInteractionWidget)
	{
		ActiveInteractionWidget->RemoveFromParent();
		ActiveInteractionWidget = nullptr;
	}
}

