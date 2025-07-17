// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "SaveSpot.h"

//Engine Includes
#include "Components/BoxComponent.h"

ASaveSpot::ASaveSpot()
{
	SaveBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SaveBox->SetupAttachment(RootComponent);

	InteractionBox->SetupAttachment(SaveBox);
}
