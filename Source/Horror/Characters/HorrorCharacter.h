// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Project Includes

//Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "HorrorCharacter.generated.h"

class AInteractable;
class AItem;
class UInventoryComponent;

class UCameraComponent;
class USpringArmComponent;

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class HORROR_API AHorrorCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorCharacter();

	/** Returns Mesh1P subobject **/
	//USkeletalMeshComponent* GetMesh1P() const { return ArmsMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

#pragma region CoreComponents
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//USkeletalMeshComponent* ArmsMesh;

	///* Spring Arm */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//USpringArmComponent* SpringArmComp;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MonitorMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* HidingMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InventoryMappingContext;

#pragma endregion

#pragma region Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Inventory;
#pragma endregion

#pragma region Interaction

	/// <summary>
	/// How far the player can reach to interact with objects
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractReach = 300.0f;
	/// <summary>
	/// Called in Tick, detects if player is looking at an actor of type Interactable. Assigns LookAtActor if so
	/// </summary>
	void InteractTrace();

	/// <summary>
	/// Actor of base Interactable player is currently looking at
	/// </summary>
	AInteractable* LookAtActor = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EnterMonitor(AActor* viewTarget);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExitMonitor();

	UFUNCTION(BlueprintImplementableEvent)
	void EnterHiding();

	UFUNCTION(BlueprintImplementableEvent)
	void ExitHiding();

	UFUNCTION(BlueprintCallable)
	void InteractWithHiding(AHidingSpot* hidingSpot);

	/// <summary>
	/// Reference to hiding spot player is currently in. Null is no hiding spot.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AHidingSpot* HidingSpot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHiding = false;

#pragma endregion

#pragma region Items

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItem* HeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* InventoryComponent;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HoldItem(AItem* ItemToHold);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DropItem();


#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float WalkSpeed = 250.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float RunSpeed = 450.0f;

#pragma region Input Action Bound Functions

	UFUNCTION(BlueprintImplementableEvent)
	void Pause();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Exit(const FInputActionValue& Value);
	void Whistle(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void EnterTablet();

	UFUNCTION(BlueprintImplementableEvent)
	void ExitTablet();

	void StartRun();
	void EndRun();

	UFUNCTION(BlueprintImplementableEvent)
	void StartCrouch();

	UFUNCTION(BlueprintImplementableEvent)
	void EndCrouch();

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

	void HoldItemAction();
	void ReleaseItemAction();

	void CancelItemAction();

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleInventory(bool toggle);

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraIndex(int CameraIndex);

#pragma endregion

#pragma region Whistle
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWhistle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanWhistle = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds, meta = (AllowPrivateAccess = "true"))
	USoundBase* WhistleCue;

#pragma endregion

#pragma region Controls

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SwitchToDefaultControls();

	UFUNCTION(BlueprintCallable)
	void SwitchToMonitorControls();

	UFUNCTION(BlueprintCallable)
	void SwitchToHidingControls();

	UFUNCTION(BlueprintCallable)
	void SwitchToInventoryControls();

#pragma endregion

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

#pragma region Animations
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayChargeThrowAnimation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayThrowAnimation();

#pragma endregion

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
