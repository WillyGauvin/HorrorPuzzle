// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Banana.generated.h"

class UBoxComponent;
/**
 *
 */
UCLASS()
class HORROR_API ABanana : public AItem
{
	GENERATED_BODY()

public:

	ABanana();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Banana;
};
