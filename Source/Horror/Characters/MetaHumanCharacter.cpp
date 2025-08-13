// Fill out your copyright notice in the Description page of Project Settings.


#include "Horror/Characters/MetaHumanCharacter.h"

// Sets default values
AMetaHumanCharacter::AMetaHumanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMetaHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMetaHumanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMetaHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

