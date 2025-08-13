// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Project Includes
#include "Horror/Interactable/Interactable.h"

//Engine Includes
#include "CoreMinimal.h"
#include "Door.generated.h"


class UBoxComponent;
class UPaperSpriteComponent;
class UPaperSprite;

//Enum type for future case that Monkey can open doors.
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Frame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* FrontInteractionLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* BackInteractionLocation;

#pragma region MiniMap

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* MinimapIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* OpenSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* ClosedSprite;

#pragma endregion

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Opening/Closing
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
#pragma endregion

#pragma region Interaction
	virtual FString InteractWith_Implementation(AActor* otherActor) override;

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

	AActor* CurrentOverlappingActor = nullptr;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;
};
