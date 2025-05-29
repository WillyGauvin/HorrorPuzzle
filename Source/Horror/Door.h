// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class HORROR_API ADoor : public AInteractable
{
	GENERATED_BODY()

	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Frame;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	bool bIsOpen = false;

	void ToggleDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	UFUNCTION(BlueprintImplementableEvent)
	void Close();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenPosZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ClosePosZ;
};
