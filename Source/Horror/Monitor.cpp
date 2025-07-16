// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitor.h"
#include "Components/BoxComponent.h"

AMonitor::AMonitor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ControlMonitorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControlFrame"));
	ControlMonitorFrame->SetupAttachment(Root);

	ControlMonitorScreen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControlScreen"));
	ControlMonitorScreen->SetupAttachment(ControlMonitorFrame);

	CameraMonitorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraFrame"));
	CameraMonitorFrame->SetupAttachment(Root);

	CameraMonitorScreen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraScreen"));
	CameraMonitorScreen->SetupAttachment(CameraMonitorFrame);

	InteractionBox->SetupAttachment(Root);
}