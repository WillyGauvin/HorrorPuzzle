// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Project Includes
#include "Interactable.h"

//Engine Includes
#include "CoreMinimal.h"
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
	UStaticMeshComponent* HidingSpotMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	/// <summary>
	/// Position Interacting Actor will be placed in when entering hiding place
	/// </summary>
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector InPosition;

	/// <summary>
	/// Position Interacting Actor will be placed in when exiting hiding place
	/// </summary>
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector OutPosition;

	/// <summary>
	/// Distance Character will be raised when peeking out of hiding place
	/// </summary>
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PeekZPos;
};
