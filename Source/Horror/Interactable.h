// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UUserWidget* ActiveInteractionWidget;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString InteractWith(AActor* otherActor);

	virtual FString InteractWith_Implementation(AActor* otherActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartLookAt(APlayerController* PlayerController);

	virtual void StartLookAt_Implementation(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopLookAt();

	virtual void StopLookAt_Implementation();

	FString ID = "";

};
