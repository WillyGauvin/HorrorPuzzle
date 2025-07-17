// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "Interactable.h"
#include "Horror/Characters/HorrorCharacter.h"

//Engine Includes
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable::AInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create box that triggers all interaction logic
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block); //ECC_GameTraceChannel 1 is custom trace channel called Interaction

	OuterImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/Textures/InteractionIcons/InteractOuter.InteractOuter")));
	InnerImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/Textures/InteractionIcons/InteractInner.InteractInner")));

	OuterInteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterInteractSphere->SetupAttachment(InteractionBox);
	OuterInteractSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OuterInteractSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	OuterInteractSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnSphereBeginOverlap);
	OuterInteractSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnSphereEndOverlap);
	OuterInteractSphere->SetSphereRadius(500.0f);

	OuterBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("OuterBillboard"));
	OuterBillboard->SetupAttachment(OuterInteractSphere);
	OuterBillboard->SetVisibility(false);
	OuterBillboard->SetHiddenInGame(false);
	OuterBillboard->SetSprite(OuterImage);
	OuterBillboard->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));

	InnerInteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerInteractSphere->SetupAttachment(InteractionBox);
	InnerInteractSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InnerInteractSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	InnerInteractSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnSphereBeginOverlap);
	InnerInteractSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnSphereEndOverlap);
	InnerInteractSphere->SetSphereRadius(250.0f);


	InnerBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("InnerBillboard"));
	InnerBillboard->SetupAttachment(InnerInteractSphere);
	InnerBillboard->SetVisibility(false);
	InnerBillboard->SetHiddenInGame(false);
	InnerBillboard->SetSprite(InnerImage);
	InnerBillboard->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));



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
	//Reset Widget in case of widget changes between interactions
	if (ActiveInteractionWidget)
	{
		ActiveInteractionWidget->RemoveFromParent();
		ActiveInteractionWidget = nullptr;
	}

	if (InteractionWidgetClass && PlayerController)
	{
		ActiveInteractionWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);

		if (ActiveInteractionWidget)
		{
			ActiveInteractionWidget->AddToViewport();
		}
	}
}

void AInteractable::ReloadWidget()
{
	if (ActiveInteractionWidget)
	{
		ActiveInteractionWidget->RemoveFromParent();
		ActiveInteractionWidget = nullptr;
	}

	ActiveInteractionWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InteractionWidgetClass);

	if (ActiveInteractionWidget)
	{
		ActiveInteractionWidget->AddToViewport();
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

void AInteractable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetVelocity().IsNearlyZero() || !bIsInteractable)
	{
		OuterBillboard->SetVisibility(false);
		InnerBillboard->SetVisibility(false);
		return;
	}
	if (OtherActor->IsA(AHorrorCharacter::StaticClass()))
	{
		if (OverlappedComponent == OuterInteractSphere)
		{
			OuterBillboard->SetVisibility(true);
		}
		else if (OverlappedComponent == InnerInteractSphere)
		{
			//Don't want to see outer Billboard when we enter within inner billboards range
			OuterBillboard->SetVisibility(false);
			InnerBillboard->SetVisibility(true);
		}
	}
}

void AInteractable::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!GetVelocity().IsNearlyZero() || !bIsInteractable)
	{
		OuterBillboard->SetVisibility(false);
		InnerBillboard->SetVisibility(false);
		return;
	}
	if (OtherActor->IsA(AHorrorCharacter::StaticClass()))
	{
		if (OverlappedComponent == OuterInteractSphere)
		{
			OuterBillboard->SetVisibility(false);
		}
		else if (OverlappedComponent == InnerInteractSphere)
		{
			InnerBillboard->SetVisibility(false);
			OuterBillboard->SetVisibility(true);
		}
	}
}

void AInteractable::SetInteractability(bool isInteractable)
{
	bIsInteractable = isInteractable;

	if (bIsInteractable)
	{
		ManualCheckInteractionSphere();
	}
	else
	{
		InnerBillboard->SetVisibility(false);
		OuterBillboard->SetVisibility(false);
	}


}

void AInteractable::ManualCheckInteractionSphere()
{
	if (InnerInteractSphere->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		InnerBillboard->SetVisibility(true);
		return;
	}
	if (OuterInteractSphere->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		OuterBillboard->SetVisibility(true);
		return;
	}
}

