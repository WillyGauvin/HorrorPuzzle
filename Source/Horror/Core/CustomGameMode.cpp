// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomGameState.h"


ACustomGameMode::ACustomGameMode()
{
	GameStateClass = ACustomGameState::StaticClass();
}

int ACustomGameMode::GetDoorsOpenedWithoutBreak() const
{
	return GetGameState<ACustomGameState>()->DoorsOpenedWithoutBreak;
}

void ACustomGameMode::AddDoorsOpenedWithoutBreak() const
{
	GetGameState<ACustomGameState>()->DoorsOpenedWithoutBreak += 1;
}

void ACustomGameMode::ResetDoorsOpenedWithoutBreak() const
{
	GetGameState<ACustomGameState>()->DoorsOpenedWithoutBreak = 0;
}
