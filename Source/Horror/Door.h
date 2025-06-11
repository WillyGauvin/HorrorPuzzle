// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"


UENUM(BlueprintType)
enum class EInteractType : uint8
{
	ControlRoom,
	Player,
	Monkey,
};
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpen = false;

	UFUNCTION(BlueprintCallable)
	void ToggleDoor(EInteractType interactType);

	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	UFUNCTION(BlueprintImplementableEvent)
	void Close();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenManually();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseManually();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenPosZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ClosePosZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LiftedPosZ;
};
