// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "Item.h"

AItemSpawner::AItemSpawner()
{

}

void AItemSpawner::SpawnItem()
{
	if (!bHasSpawned && ItemToSpawn != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(ItemToSpawn, GetActorTransform(), SpawnParams);

		bHasSpawned = true;
	}
}
