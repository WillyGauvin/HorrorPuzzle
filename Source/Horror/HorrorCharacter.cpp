// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interactable.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	EndRun();
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
	if (bCanWhistle && Stamina - WhistleStaminaCost > 0.0f)
	{
		PlayWhistle();
		Stamina = FMath::Max(0.0f, Stamina - WhistleStaminaCost);
	}
}

void AHorrorCharacter::StartRun()
{
	if (Stamina > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsRunning = true;
	}
}

void AHorrorCharacter::EndRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsRunning = false;
}

#pragma region SwitchCamera

void AHorrorCharacter::SwitchCamera0()
{
	SwitchCameraIndex(0);
}
void AHorrorCharacter::SwitchCamera1()
{
	SwitchCameraIndex(1);
}
void AHorrorCharacter::SwitchCamera2()
{
	SwitchCameraIndex(2);
}
void AHorrorCharacter::SwitchCamera3()
{
	SwitchCameraIndex(3);
}
void AHorrorCharacter::SwitchCamera4()
{
	SwitchCameraIndex(4);
}
void AHorrorCharacter::SwitchCamera5()
{
	SwitchCameraIndex(5);
}
void AHorrorCharacter::SwitchCamera6()
{
	SwitchCameraIndex(6);
}
void AHorrorCharacter::SwitchCamera7()
{
	SwitchCameraIndex(7);
}
void AHorrorCharacter::SwitchCamera8()
{
	SwitchCameraIndex(8);
}
void AHorrorCharacter::SwitchCamera9()
{
	SwitchCameraIndex(9);
}

#pragma endregion


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

	if (Stamina <= 0.0f && bIsRunning)
	{
		EndRun();
	}

	if (bIsRunning)
	{
		Stamina = FMath::Max(0.0f, Stamina - DeltaTime);
		//GEngine->AddOnScreenDebugMessage(
		//	-1,                      // Unique key (use -1 for new message)
		//	1.0f,                    // Duration in seconds
		//	FColor::Yellow,          // Text color
		//	FString::Printf(TEXT("StaminaRegenCoolDownRemaining: %f"), StaminaRegenCooldownRemaining)
		//);

		//GEngine->AddOnScreenDebugMessage(
		//	-1,
		//	5.0f,
		//	FColor::Red,
		//	FString::Printf(TEXT("Stamina: %f"), Stamina)
		//);
	}
	else
	{
		Stamina = FMath::Min(MaxStamina, Stamina + DeltaTime * StaminaRegenRate);
	}
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

		//Tablet
		EnhancedInputComponent->BindAction(TabletAction, ETriggerEvent::Started, this, &AHorrorCharacter::EnterTablet);
		EnhancedInputComponent->BindAction(TabletAction, ETriggerEvent::Completed, this, &AHorrorCharacter::ExitTablet);

		//Run
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AHorrorCharacter::StartRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AHorrorCharacter::EndRun);

		//Switch Cameras
		EnhancedInputComponent->BindAction(SwitchCameraAction1, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera0);
		EnhancedInputComponent->BindAction(SwitchCameraAction2, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera1);
		EnhancedInputComponent->BindAction(SwitchCameraAction3, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera2);
		EnhancedInputComponent->BindAction(SwitchCameraAction4, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera3);
		EnhancedInputComponent->BindAction(SwitchCameraAction5, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera4);
		EnhancedInputComponent->BindAction(SwitchCameraAction6, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera5);
		EnhancedInputComponent->BindAction(SwitchCameraAction7, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera6);
		EnhancedInputComponent->BindAction(SwitchCameraAction8, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera7);
		EnhancedInputComponent->BindAction(SwitchCameraAction9, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera8);
		EnhancedInputComponent->BindAction(SwitchCameraAction0, ETriggerEvent::Completed, this, &AHorrorCharacter::SwitchCamera9);

		//Peeking
		EnhancedInputComponent->BindAction(PeekAction, ETriggerEvent::Started, this, &AHorrorCharacter::Peek);
		EnhancedInputComponent->BindAction(PeekAction, ETriggerEvent::Completed, this, &AHorrorCharacter::UnPeek);

		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AHorrorCharacter::ChargeBanana);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &AHorrorCharacter::ThrowBanana);
	}
}

void AHorrorCharacter::SwitchToDefaultControls()
{
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(MonitorMappingContext);
			Subsystem->RemoveMappingContext(HidingMappingContext);
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

void AHorrorCharacter::SwitchToHidingControls()
{
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(HidingMappingContext, 1);
		}
	}
}

void AHorrorCharacter::InteractWithHiding(AHidingSpot* hidingSpot)
{
	if (HidingSpot == nullptr)
	{
		HidingSpot = hidingSpot;
		EnterHiding();
	}
	else
	{
		ExitHiding();
	}

}

UAISense_Sight::EVisibilityResult AHorrorCharacter::CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData, const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	/* If I add a mesh to the character use this */
	//FVector SightTargetLocation = GetMesh()->GetSocketLocation("head");

	FVector SightTargetLocation = GetActorLocation() + FVector(0.0f,0.0f,60.0f);
	FHitResult HitResult;

	bool HadBlockingHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Context.ObserverLocation,
		SightTargetLocation,
		ECC_Visibility,
		FCollisionQueryParams(FName("Name_AILineOfSight"), false, Context.IgnoreActor)
	);

	AActor* HitActor = Cast<AActor>(HitResult.GetActor());

	if (!HadBlockingHit || (IsValid(HitActor) && HitActor->IsOwnedBy(this)))
	{
		OutSeenLocation = HadBlockingHit ? HitResult.ImpactPoint : SightTargetLocation;
		OutNumberOfLoSChecksPerformed = 1;
		OutNumberOfAsyncLosCheckRequested = 0;
		OutSightStrength = 1;
		return UAISense_Sight::EVisibilityResult::Visible;
	}

	OutNumberOfLoSChecksPerformed = 1;
	OutNumberOfAsyncLosCheckRequested = 0;
	OutSightStrength = 0;
	return UAISense_Sight::EVisibilityResult::NotVisible;
}
