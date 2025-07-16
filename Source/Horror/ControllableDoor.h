// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "ControllableDoor.generated.h"


class UChildActorComponent;
/**
 *
 */
UCLASS()
class HORROR_API AControllableDoor : public ADoor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* DoorWidgetLocation;

public:

	AControllableDoor();

	virtual void ToggleDoor(EInteractType interactType) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBroken;

	bool TryBreakDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void BreakDoor();//Handles setting bIsBroken, Widget Image, and any animations for breaking.

	UFUNCTION(BlueprintImplementableEvent)
	void FixDoor(); //Handles setting bIsBroken, Widget Image, and any quick time events for fixing.

	UFUNCTION(BlueprintImplementableEvent)
	void OpenManually();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseManually();

	UFUNCTION(BlueprintCallable)
	FVector GetDoorLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LiftedPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DoorCode;
};
