// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSpot.h"
#include "Components/BoxComponent.h"

ASaveSpot::ASaveSpot()
{
	SaveBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SaveBox->SetupAttachment(RootComponent);

	InteractionBox->SetupAttachment(SaveBox);
}
