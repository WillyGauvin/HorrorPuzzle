// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "DoorController.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class HORROR_API ADoorController : public AInteractable
{
	GENERATED_BODY()

	ADoorController();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Box;

public:

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADoor* LinkedDoor = nullptr;
};
