// Fill out your copyright notice in the Description page of Project Settings.

//Project Includes
#include "Horror/Characters/HorrorCharacter.h"
#include "Horror/Interactable/Interactable.h"
#include "Horror/Interactable/Items/Item.h"
#include "Horror/Interactable/Items/InventoryComponent.h"
#include "Horror/Characters/EnemyCharacter.h"

//Engine Includes
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"

#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	//SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	//SpringArmComp->SetupAttachment(GetMesh());
	//SpringArmComp->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	//SpringArmComp->bUsePawnControlRotation = true;
	//SpringArmComp->bEnableCameraLag = true;
	//SpringArmComp->bEnableCameraRotationLag = true;
	//SpringArmComp->CameraRotationLagSpeed = 20.0f;
	//SpringArmComp->TargetArmLength = 0.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));
	CameraComponent->bUsePawnControlRotation = true;

	//ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	//ArmsMesh->SetOnlyOwnerSee(true);
	//ArmsMesh->SetupAttachment(CameraComponent);
	//ArmsMesh->bCastDynamicShadow = false;
	//ArmsMesh->CastShadow = false;
	//ArmsMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
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


void AHorrorCharacter::HoldItemAction()
{
	if (HeldItem)
	{
		HeldItem->HoldAction();
	}
}

void AHorrorCharacter::ReleaseItemAction()
{
	if (HeldItem)
	{
		HeldItem->ReleaseAction();
	}
}

void AHorrorCharacter::CancelItemAction()
{
	if (HeldItem)
	{
		HeldItem->CancelAction();
	}
}

#pragma endregion


void AHorrorCharacter::InteractTrace()
{
	FHitResult Hit;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * InteractReach;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the actor performing the trace
	QueryParams.AddIgnoredActor(UGameplayStatics::GetActorOfClass(this, AEnemyCharacter::StaticClass())); //Ignore the chimp, don't ever need to interact with it.

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, QueryParams); //ECC_GametraceChannel1 is a custom Interaction Trace channel. All Actors of base Interactable have a collision box set to block this channel

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

	//Deplete Stamina if we are running
	if (bIsRunning)
	{
		Stamina = FMath::Max(0.0f, Stamina - DeltaTime);
	}
	//Regenerate Stamina if we are not running
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
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &AHorrorCharacter::Pause);

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

		//Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AHorrorCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AHorrorCharacter::EndCrouch);

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

		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AHorrorCharacter::HoldItemAction);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &AHorrorCharacter::ReleaseItemAction);

		EnhancedInputComponent->BindAction(Inventory, ETriggerEvent::Started, this, &AHorrorCharacter::ToggleInventory, true);
		EnhancedInputComponent->BindAction(Inventory, ETriggerEvent::Completed, this, &AHorrorCharacter::ToggleInventory, false);
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
			Subsystem->RemoveMappingContext(InventoryMappingContext);
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

void AHorrorCharacter::SwitchToInventoryControls()
{
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(InventoryMappingContext, 1);
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
	/* If I add a mesh to the character use this so we can only be detected from our head socket, not the entire body. Better game feel if we only get detected if have the ability to see the enemy */
	//FVector SightTargetLocation = GetMesh()->GetSocketLocation("head");

	FVector SightTargetLocation = GetActorLocation();
	//Add offset for where the player head would be
	SightTargetLocation += FVector(0.0f, 0.0f, 60.0f);

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
