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

	/// <summary>
	/// Widget class to show when Character is able to interact with
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* ActiveInteractionWidget;

	/// <summary>
	/// Called when otherActor interacts with
	/// </summary>
	/// <param name="otherActor"> Actor Interacting with</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString InteractWith(AActor* otherActor);

	virtual FString InteractWith_Implementation(AActor* otherActor);

	/// <summary>
	/// Called when Character looks at
	/// </summary>
	/// <param name="PlayerController"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartLookAt(APlayerController* PlayerController);

	virtual void StartLookAt_Implementation(APlayerController* PlayerController);

	/// <summary>
	/// Called when Character looks away from
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopLookAt();

	virtual void StopLookAt_Implementation();

	/// <summary>
	/// Force reload of Interaction Widgets. Used when Widgets are changed while Interactable is being looked at
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void ReloadWidget();


	FString ID = "";

	//Interaction Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBox;

	/// <summary>
	/// Trigger for displaying outer interaction prompts
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* OuterInteractSphere;

	/// <summary>
	/// Trigger for displaying inner interaction prompts
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* InnerInteractSphere;

	/// <summary>
	/// Outer interaction prompt
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* OuterBillboard;

	/// <summary>
	/// Inner interaction prompt
	/// </summary>
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

	/// <summary>
	/// Manually change if actor can be interacted with
	/// </summary>
	/// <param name="isInteractable"></param>
	UFUNCTION(BlueprintCallable)
	void SetInteractability(bool isInteractable);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteractable = true;

	void ManualCheckInteractionSphere();

};
