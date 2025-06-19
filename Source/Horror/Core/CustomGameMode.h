// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HORROR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	ACustomGameMode();

	UFUNCTION(BlueprintPure, Category = "Doors")
	virtual int GetDoorsOpenedWithoutBreak() const;

	UFUNCTION(BlueprintCallable, Category = "Doors")
	virtual void AddDoorsOpenedWithoutBreak() const;

	UFUNCTION(BlueprintCallable, Category = "Doors")
	virtual void ResetDoorsOpenedWithoutBreak() const;
};
