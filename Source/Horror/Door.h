// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"


class UBoxComponent;
class UPaperSpriteComponent;
class UPaperSprite;

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

public:

	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Frame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSpriteComponent* MinimapIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSprite* OpenSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSprite* ClosedSprite;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FString InteractWith_Implementation(AActor* otherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpen = false;

	UFUNCTION(BlueprintCallable)
	virtual void ToggleDoor(EInteractType interactType);

	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	UFUNCTION(BlueprintImplementableEvent)
	void Close();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OpenPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ClosePos;
};
