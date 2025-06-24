// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Horror/HorrorCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::IsRoomForItem(TSubclassOf<AItem> itemClass)
{
	return (Items[itemClass] < itemClass->GetDefaultObject<AItem>()->MaxInInventory);
}

bool UInventoryComponent::DoesHaveItem(TSubclassOf<AItem> itemClass)
{
	return (Items[itemClass] > 0);
}

bool UInventoryComponent::AddItem(TSubclassOf<AItem> itemClass)
{
	if (IsRoomForItem(itemClass))
	{
		Items[itemClass]++;
		return true;
	}
	else
	{
		return false;
	}
}

bool UInventoryComponent::RemoveItem(TSubclassOf<AItem> itemClass)
{
	if (DoesHaveItem(itemClass))
	{
		Items[itemClass]--;
		return true;
	}
	else
	{
		return false;
	}
}

bool UInventoryComponent::SelectItem(TSubclassOf<AItem> itemClass)
{
	if (!DoesHaveItem(itemClass))
	{
		return false;
	}

	if (AHorrorCharacter* Character = Cast<AHorrorCharacter>(GetOwner()))
	{
			
	}
}

