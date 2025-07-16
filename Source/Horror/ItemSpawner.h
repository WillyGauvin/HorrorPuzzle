// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawner.generated.h"

class AItem;

/**
 *
 */
UCLASS()
class HORROR_API AItemSpawner : public AActor
{
	GENERATED_BODY()

public:

	AItemSpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnItem();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UseSaveData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasSpawned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> ItemToSpawn = nullptr;
};
