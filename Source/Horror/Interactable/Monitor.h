// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Project Includes
#include "Interactable.h"

//Engine Includes
#include "CoreMinimal.h"
#include "Monitor.generated.h"

/**
 *
 */
UCLASS()
class HORROR_API AMonitor : public AInteractable
{
	GENERATED_BODY()

public:

	AMonitor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ControlMonitorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ControlMonitorScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CameraMonitorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CameraMonitorScreen;
};
