// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interactable.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Spring Arm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraRotationLagSpeed = 20.0f;
	SpringArmComp->TargetArmLength = 0.0f;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = false;

	// Create the arms mesh
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetOnlyOwnerSee(true);
	ArmsMesh->SetupAttachment(CameraComponent);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHorrorCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AHorrorCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHorrorCharacter::Interact(const FInputActionValue& Value)
{
	if (LookAtActor)
	{
		LookAtActor->InteractWith(this);
	}
}

void AHorrorCharacter::Exit(const FInputActionValue& Value)
{
	ExitMonitor();
}

void AHorrorCharacter::Whistle(const FInputActionValue& Value)
{
	PlayWhistle();
}

void AHorrorCharacter::InteractTrace()
{
	FHitResult Hit;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * 300.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the actor performing the trace

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.ObjectTypesToQuery =
		FCollisionObjectQueryParams::InitType(ECC_WorldDynamic) |
		FCollisionObjectQueryParams::InitType(ECC_WorldStatic) |
		FCollisionObjectQueryParams::InitType(ECC_Pawn);  // Exclude custom Sphere type

	bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, QueryParams); //Might need to change channel from ECC_Visibility. Depending on what kind of actor we use

	bool StoppedLookingAt = true;

	if (bHit)
	{
		// A hit occurred
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (AInteractable* Interactable = Cast<AInteractable>(HitActor))
			{
				// This covers the case where the player is looking at an interactable and then in the next frame is looking at another interactable.
				if (LookAtActor != Interactable)
				{
					if (LookAtActor != nullptr)
					{
						LookAtActor->StopLookAt();
					}
					LookAtActor = Interactable;

					LookAtActor->StartLookAt(Cast<APlayerController>(Controller));
				}
				StoppedLookingAt = false;
			}
		}
	}

	if (StoppedLookingAt)
	{
		if (LookAtActor != nullptr)
		{
			LookAtActor->StopLookAt();
			LookAtActor = nullptr;
		}
	}
}


// Called every frame
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractTrace();
}

void AHorrorCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHorrorCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHorrorCharacter::Look);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AHorrorCharacter::Interact);

		//Exit Monitor
		EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Completed, this, &AHorrorCharacter::Exit);

		//Whistle
		EnhancedInputComponent->BindAction(WhistleAction, ETriggerEvent::Completed, this, &AHorrorCharacter::Whistle);
	}
}

void AHorrorCharacter::SwitchToDefaultControls()
{
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(MonitorMappingContext);
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
		}
	}
}

void AHorrorCharacter::SwitchToMonitorControls()
{
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(MonitorMappingContext, 1);
		}
	}
}

