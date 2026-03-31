// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Characters/Lore/TekuaniMarcelaLoreCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/Interaction/TekuaniInteractable.h"

ATekuaniMarcelaLoreCharacter::ATekuaniMarcelaLoreCharacter()
{
	// Configure collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 75.f);

	/**
	 * Controller rotation is disabled to avoid direct camera-driven rotation.
	 *
	 * In exploration gameplay, rotation behavior is typically controlled
	 * by movement logic or camera orientation rather than raw controller input.
	 */
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	InitializeCamera();
	ConfigureMovement();
}

void ATekuaniMarcelaLoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/**
	 * Overlap events are used to detect nearby actors that can be interacted with.
	 * 
	 * This avoids performing expensive traces every frame.
	 */
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATekuaniMarcelaLoreCharacter::OnLoreMarcelaBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ATekuaniMarcelaLoreCharacter::OnLoreMarcelaEndOverlap);
}

void ATekuaniMarcelaLoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Cast<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(LoreMappingContext, 0);
	}
	
	if (UEnhancedInputComponent* LoreEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		LoreEnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATekuaniMarcelaLoreCharacter::MoveEnhanced);
		LoreEnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &ATekuaniMarcelaLoreCharacter::InteractEnhanced);
		LoreEnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		LoreEnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}


void ATekuaniMarcelaLoreCharacter::MoveEnhanced(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void ATekuaniMarcelaLoreCharacter::InteractEnhanced(const FInputActionValue& Value)
{
	/**
	 * If a valid interactable actor is currently detected,
	 * trigger its interaction behavior through the interface.
	 */
	if (CurrentInteractableActor)
		ITekuaniInteractable::Execute_Interact(CurrentInteractableActor, this);
}

void ATekuaniMarcelaLoreCharacter::OnLoreMarcelaBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	/**
	 * Store the actor as interactable if it implements the interaction interface.
	 */
	if (OtherActor && OtherActor->Implements<UTekuaniInteractable>())
		CurrentInteractableActor = OtherActor;
		
}

void ATekuaniMarcelaLoreCharacter::OnLoreMarcelaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor == CurrentInteractableActor))
		CurrentInteractableActor = nullptr;
}

void ATekuaniMarcelaLoreCharacter::InitializeCamera()
{
	/**
	 * Spring arm is used to maintain a consistent camera distance
	 * and provide smooth camera behavior.
	 */
	LoreMarcelaCameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	LoreMarcelaCameraBoom->SetupAttachment(GetRootComponent());

	// 500 units chosen to maintain consistent spatial readability
	// for medium-scale combat and traversal scenarios.
	LoreMarcelaCameraBoom->TargetArmLength = 500.0f;

	// Offset tuned to improve character framing in 2.5D perspective.
	LoreMarcelaCameraBoom->SocketOffset = FVector(0.f, 0.f, 180.f);

	// Allows controller input to rotate the camera boom.
	LoreMarcelaCameraBoom->bUsePawnControlRotation = true;

	// Create Follow Camera
	LoreMarcelaCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	LoreMarcelaCamera->SetupAttachment(LoreMarcelaCameraBoom, USpringArmComponent::SocketName);

	// Camera rotation handled by spring arm, not directly by pawn.
	LoreMarcelaCamera->bUsePawnControlRotation = false;
}

void ATekuaniMarcelaLoreCharacter::ConfigureMovement()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();

	// Disable automatic rotation toward movement direction.
	// Rotation behavior may later be driven by custom logic or GAS.
	Movement->bOrientRotationToMovement = false;

	// High Z rotation rate for responsive lateral direction changes.
	Movement->RotationRate = FRotator(0.f, 0.f, 0.f);

	// Default walk speed tuned for responsive gameplay feel.
	Movement->MaxWalkSpeed = 600.0f;

	// Braking tuned for tighter stopping control.
	Movement->BrakingDecelerationWalking = 2000.f;
}

