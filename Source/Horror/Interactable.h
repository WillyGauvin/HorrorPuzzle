// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"


class USphereComponent;
class UBoxComponent;
class UBillboardComponent;

UCLASS()
class HORROR_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* ActiveInteractionWidget;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString InteractWith(AActor* otherActor);

	virtual FString InteractWith_Implementation(AActor* otherActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartLookAt(APlayerController* PlayerController);

	virtual void StartLookAt_Implementation(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopLookAt();

	UFUNCTION(BlueprintCallable)
	void ReloadWidget();

	virtual void StopLookAt_Implementation();

	FString ID = "";

	//Interaction Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* OuterInteractSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* InnerInteractSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* OuterBillboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* InnerBillboard;

	UTexture2D* OuterImage;
	UTexture2D* InnerImage;

	//Interaction Logic
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SetInteractability(bool isInteractable);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteractable = true;

	void ManualCheckInteractionSphere();

};
