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
	UPaperSpriteComponent* MinimapIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSprite* OpenSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperSprite* ClosedSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* FrontInteractionLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* BackInteractionLocation;
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


	//Interaction

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> OpenDoorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CloseDoorWidgetClass;

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	void SetBillboardLocations(AActor* OtherActor);

	bool bIsOverlapping = false;
	AActor* CurrentOverlappingActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;
};
