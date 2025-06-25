// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Horror/Item.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryChangedDelegate, TSubclassOf<AItem>, itemClass, int, numInInventory);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AItem>, int> Items;

	bool IsRoomForItem(TSubclassOf<AItem> itemClass);

	bool DoesHaveItem(TSubclassOf<AItem> itemClass);

	bool AddItem(TSubclassOf<AItem> itemClass);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(TSubclassOf<AItem> itemClass);

	UFUNCTION(BlueprintCallable)
	bool SelectItem(TSubclassOf<AItem> itemClass);

	UFUNCTION(BlueprintCallable)
	int GetNumItems(TSubclassOf<AItem> itemClass);

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FInventoryChangedDelegate OnInventoryChangedDelegate;
};
