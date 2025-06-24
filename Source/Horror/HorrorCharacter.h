// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "HorrorCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AInteractable;
struct FInputActionInstance;
class AHidingSpot;
class AItem;
class UInventoryComponent;

UCLASS()
class HORROR_API AHorrorCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorCharacter();

#pragma region CoreComponents
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ArmsMesh;

	/* Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MonitorMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* HidingMappingContext;
#pragma endregion

#pragma region Actions

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ExitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* WhistleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TabletAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RunAction;

#pragma region SwitchCamera
	//SwitchCamera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction8;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction9;
#pragma endregion SwitchCamera

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PeekAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrowAction;
#pragma endregion Actions

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundBase* WhistleCue;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Exit(const FInputActionValue& Value);
	void Whistle(const FInputActionValue& Value);
	void StartRun();
	void EndRun();
	void SwitchCamera0();
	void SwitchCamera1();
	void SwitchCamera2();
	void SwitchCamera3();
	void SwitchCamera4();
	void SwitchCamera5();
	void SwitchCamera6();
	void SwitchCamera7();
	void SwitchCamera8();
	void SwitchCamera9();

	UFUNCTION(BlueprintImplementableEvent)
	void Peek();
	UFUNCTION(BlueprintImplementableEvent)
	void UnPeek();

	UFUNCTION(BlueprintImplementableEvent)
	void ChargeBanana();

	UFUNCTION(BlueprintImplementableEvent)
	void ThrowBanana();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraIndex(int CameraIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayWhistle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanWhistle = true;

	void InteractTrace();
	AInteractable* LookAtActor = nullptr;

	// APawn interface

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// End of APawn interface

	UFUNCTION(BlueprintCallable)
	void SwitchToDefaultControls();

	UFUNCTION(BlueprintCallable)
	void SwitchToMonitorControls();

	UFUNCTION(BlueprintCallable)
	void SwitchToHidingControls();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float WalkSpeed = 400.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float RunSpeed = 650.0f;


#pragma region Stamina

	float bIsRunning = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxStamina = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Stamina = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StaminaRegenRate = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WhistleStaminaCost = 2.0f;

#pragma endregion


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return ArmsMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EnterMonitor(FTransform ViewLocation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExitMonitor();

	UFUNCTION(BlueprintImplementableEvent)
	void EnterTablet();

	UFUNCTION(BlueprintImplementableEvent)
	void ExitTablet();

	UFUNCTION(BlueprintImplementableEvent)
	void EnterHiding();

	UFUNCTION(BlueprintImplementableEvent)
	void ExitHiding();

	UFUNCTION(BlueprintCallable)
	void InteractWithHiding(AHidingSpot* hidingSpot);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AHidingSpot* HidingSpot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHiding = false;

#pragma region Items

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItem* HeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* InventoryComponent;


#pragma endregion Items




	private:
		virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(
			const FCanBeSeenFromContext& Context,
			FVector& OutSeenLocation,
			int32& OutNumberOfLoSChecksPerformed,
			int32& OutNumberOfAsyncLosCheckRequested,
			float& OutSightStrength,
			int32* UserData = nullptr,
			const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr
		) override;

};
