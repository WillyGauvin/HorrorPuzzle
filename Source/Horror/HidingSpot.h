// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "HidingSpot.generated.h"


class AHorrorCharacter;

/**
 * 
 */
UCLASS()
class HORROR_API AHidingSpot : public AInteractable
{
	GENERATED_BODY()
	
	AHidingSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Object;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector InPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector OutPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PeekZPos;
};
