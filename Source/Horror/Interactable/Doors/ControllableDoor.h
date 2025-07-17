// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Project Includes
#include "Door.h"

//Engine Includes
#include "CoreMinimal.h"
#include "ControllableDoor.generated.h"


class UChildActorComponent;
/**
 * Controllable Doors are controllable from Monitors. Logic inherited from base class ADoor is used for controlling from Monitors.
 * Open/Close Manually functions used for in person interaction.
 */
UCLASS()
class HORROR_API AControllableDoor : public ADoor
{
	GENERATED_BODY()

public:


	AControllableDoor();

	virtual void ToggleDoor(EInteractType interactType) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBroken;

	bool TryBreakDoor();

	/// <summary>
	/// Breaks the door, handles all logic for getting door to broken state
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void BreakDoor();

	/// <summary>
	/// Attempts to fix door, handles all logic and QTE's for attempting to fix door. Fixes door if QTE is completed
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void FixDoor();

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

	/// <summary>
	/// Location Widget to open/close doors will appear at on the monitors/tablet
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* DoorWidgetLocation;
};
