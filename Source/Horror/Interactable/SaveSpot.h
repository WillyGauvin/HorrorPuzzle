// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Project Includes
#include "Interactable.h"

//Engine Includes
#include "CoreMinimal.h"
#include "SaveSpot.generated.h"

/**
 * 
 */
UCLASS()
class HORROR_API ASaveSpot : public AInteractable
{
	GENERATED_BODY()

public:

	ASaveSpot();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SaveBox;
};
