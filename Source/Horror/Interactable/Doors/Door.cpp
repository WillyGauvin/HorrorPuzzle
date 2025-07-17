// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "Door.h"
#include "Horror/Characters/HorrorCharacter.h"
#include "Horror/Core/CustomGameMode.h"

//Engine Includes
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"

#include "DrawDebugHelpers.h"

ADoor::ADoor()
{
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Frame);


	MinimapIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapIcon"));
	MinimapIcon->SetupAttachment(Frame);

	if (ClosedSprite)
	{
		MinimapIcon->SetSprite(ClosedSprite);
	}

	InteractionBox->SetupAttachment(Door);

	FrontInteractionLocation = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontInteractionIcon"));
	FrontInteractionLocation->SetupAttachment(Door);

	BackInteractionLocation = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackInteractionIcon"));
	BackInteractionLocation->SetupAttachment(Door);

	InteractionWidgetClass = (bIsOpen) ? CloseDoorWidgetClass : OpenDoorWidgetClass;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentOverlappingActor)
	{
		SetBillboardLocations(CurrentOverlappingActor);
	}
}

FString ADoor::InteractWith_Implementation(AActor* otherActor)
{
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
		if (bIsOpen)
		{
			InteractionWidgetClass = OpenDoorWidgetClass;
			Close();
		}
		else
		{
			InteractionWidgetClass = CloseDoorWidgetClass;
			Open();
		}
		ReloadWidget();
		break;
	case EInteractType::Monkey:
		break;
	}
}

void ADoor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHorrorCharacter::StaticClass()))
	{
		CurrentOverlappingActor = OtherActor;
	}

	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ADoor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHorrorCharacter::StaticClass()))
	{
		if (OverlappedComponent == OuterInteractSphere)
		{
			CurrentOverlappingActor = nullptr;
		}
	}

	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

/// <summary>
/// Sets location of Outer & Inner Interaction Billboard based on OtherActors location.
/// </summary>
/// <param name="OtherActor"></param>
void ADoor::SetBillboardLocations(AActor* OtherActor)
{
	FVector DirectionToOtherActor = OtherActor->GetActorLocation() - Door->GetComponentLocation();
	float dotProduct = FVector::DotProduct(Door->GetRightVector(), DirectionToOtherActor);

	if (bDebug)
	{
		DrawDebugLine(GetWorld(), Door->GetComponentLocation(), Door->GetComponentLocation() + DirectionToOtherActor, FColor::Blue);
		DrawDebugLine(GetWorld(), Door->GetComponentLocation(), Door->GetComponentLocation() + Door->GetRightVector() * DirectionToOtherActor.Length(), FColor::Red);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Dot Product: %f"), dotProduct));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Actor: %s"), *OtherActor->GetName()));
	}

	//If we are infront of the door
	if (dotProduct > 0.0f)
	{
		OuterBillboard->SetWorldLocation(FrontInteractionLocation->GetComponentLocation());
		InnerBillboard->SetWorldLocation(FrontInteractionLocation->GetComponentLocation());
	}
	//If we are behind the door
	else
	{
		OuterBillboard->SetWorldLocation(BackInteractionLocation->GetComponentLocation());
		InnerBillboard->SetWorldLocation(BackInteractionLocation->GetComponentLocation());
	}
}


