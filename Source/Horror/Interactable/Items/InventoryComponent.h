// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Horror/Interactable/Items/Item.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryChangedDelegate, TSubclassOf<AItem>, itemClass, int, numInInventory);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadInventoryDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORROR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// List of all items in inventory
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AItem>, int> Items;

	/// <summary>
	/// Checks if passed in Item class can fit into inventory
	/// </summary>
	/// <param name="itemClass"> Item to check for</param>
	/// <returns> True if item can fit, false otherwise </returns>
	bool IsRoomForItem(TSubclassOf<AItem> itemClass);

	/// <summary>
	/// Checks if passed in itemClass is being held in inventory
	/// </summary>
	/// <param name="itemClass"> Item to check for</param>
	/// <returns>True if holding more the 0, false if holding 0</returns>
	bool DoesHaveItem(TSubclassOf<AItem> itemClass);

	/// <summary>
	/// Adds item to inventory. No creation of item class is made. Just an integer of how many. Creation of item happens in SelectItem.
	/// </summary>
	/// <param name="itemClass"></param>
	/// <returns></returns>
	bool AddItem(TSubclassOf<AItem> itemClass);

	/// <summary>
	/// Removes 1 item from inventory
	/// </summary>
	/// <param name="itemClass">Item to remove</param>
	/// <returns> true if item was removed, false if no items were in inventory to begin with</returns>
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(TSubclassOf<AItem> itemClass);

	/// <summary>
	/// Creates item and calls AHorrorCharacter to hold said item
	/// </summary>
	/// <param name="itemClass">Item to select</param>
	/// <returns>True if item was created and held successfully</returns>
	UFUNCTION(BlueprintCallable)
	bool SelectItem(TSubclassOf<AItem> itemClass);

	/// <summary>
	///
	/// </summary>
	/// <param name="itemClass">Item type to check count of</param>
	/// <returns>Number of item type currently in inventory</returns>
	UFUNCTION(BlueprintCallable)
	int GetNumItems(TSubclassOf<AItem> itemClass);

	/// <summary>
	/// For saving and loading inventory status on startup.
	/// </summary>
	/// <param name="loadItems">List of all items and count to load</param>
	UFUNCTION(BlueprintCallable)
	void LoadInventory(TMap<TSubclassOf<AItem>, int> loadItems);

	/// <summary>
	/// Delegate to update inventory UI whenever inventory changes
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FInventoryChangedDelegate OnInventoryChangedDelegate;

};
