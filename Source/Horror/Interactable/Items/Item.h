// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Horror/Interactable/Interactable.h"
#include "Item.generated.h"

/**
 *
 */
UCLASS()
class HORROR_API AItem : public AInteractable
{
	GENERATED_BODY()

public:

	AItem();

	virtual void Tick(float DeltaTime) override;

	virtual void StartLookAt_Implementation(APlayerController* PlayerController) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void HoldAction();

	UFUNCTION(BlueprintImplementableEvent)
	void ReleaseAction();

	UFUNCTION(BlueprintImplementableEvent)
	void CancelAction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pickup();

	virtual void Pickup_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Drop();

	virtual void Drop_Implementation();

	/// <summary>
	/// Check Velocity of the Item, Interaction UI won't show up if item is moving
	/// </summary>
	UFUNCTION()
	void CheckVelocity();

	FTimerHandle CheckVelocityHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsBeingHeld = false;

	/// <summary>
	/// Maximum amount of item type the player can hold in inventory
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CanPickupWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CannotPickupWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InteractionBillboardOffset;
};
