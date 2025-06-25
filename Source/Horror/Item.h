// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
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

	UFUNCTION(BlueprintImplementableEvent)
	void HoldAction();

	UFUNCTION(BlueprintImplementableEvent)
	void ReleaseAction();

	UFUNCTION(BlueprintImplementableEvent)
	void CancelAction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Pickup();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Drop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CanPickupWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CannotPickupWidgetClass;

	virtual void StartLookAt_Implementation(APlayerController* PlayerController) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;
};
