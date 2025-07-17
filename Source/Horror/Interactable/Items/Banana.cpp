// Fill out your copyright notice in the Description page of Project Settings.


#include "Banana.h"
#include "Components/BoxComponent.h"

ABanana::ABanana()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	Banana = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Banana"));
	Banana->SetupAttachment(RootComponent);
	Banana->SetSimulatePhysics(false);

	//We don't want to use Banana's mesh collision, too complex. Using Collision Box instead
	Banana->SetCollisionProfileName("NoCollision");

	InteractionBox->SetupAttachment(Banana);

	InteractionBillboardOffset = FVector(0.0f, 0.0f, 30.0f);

}