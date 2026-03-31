// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Characters/TekuaniMarcelaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperZDAnimationComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/TekuaniInputComponent.h"
#include "TekuaniGameplayTags.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "Components/Combat/MarcelaCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "EnhancedInputComponent.h"
#include "Components/Camera/MarcelaCameraComponent.h"
#include "Components/Direction/MarcelaDirectionComponent.h"

ATekuaniMarcelaCharacter::ATekuaniMarcelaCharacter()
{
	// Configure collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 75.f);
	
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	// Disable direct controller-driven rotation.
	// Rotation logic will be handled via movement or camera system.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	InitializeCamera();
	ConfigureMovement();
	
	MarcelaCombatComponent = CreateDefaultSubobject<UMarcelaCombatComponent>(TEXT("MarcelaCombatComponent"));
	DirectionComponent = CreateDefaultSubobject<UMarcelaDirectionComponent>("DirectionComponent");
}

void ATekuaniMarcelaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(TekuaniAbilitySystemComponent);
		}
	}
}

void ATekuaniMarcelaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!PlayerController) return;

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	if (!Subsystem) return;

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	
	UTekuaniInputComponent* TekuaniInputComponent = CastChecked<UTekuaniInputComponent>(PlayerInputComponent);
	
	TekuaniInputComponent->BindNativeInputAction(InputConfigDataAsset, 
		TekuaniGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Move);
	
	TekuaniInputComponent->BindNativeInputAction(InputConfigDataAsset, 
		TekuaniGameplayTags::InputTag_Look,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Look);
	
	TekuaniInputComponent->BindAbilityInputAction(
		InputConfigDataAsset, 
		this,
		&ThisClass::Input_AbilityInputPressed,
		&ThisClass::Input_AbilityInputReleased);
	
	// Special inputs
	if (UEnhancedInputComponent* ActionEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		ActionEnhancedInput->BindAction(AimAction, ETriggerEvent::Started,this, &ATekuaniMarcelaCharacter::HandleAimInput);
		ActionEnhancedInput->BindAction(AimAction, ETriggerEvent::Canceled,this, &ATekuaniMarcelaCharacter::HandleAimInput);
		ActionEnhancedInput->BindAction(AimAction, ETriggerEvent::Completed,this, &ATekuaniMarcelaCharacter::HandleAimInput);
		ActionEnhancedInput->BindAction(ShootAction, ETriggerEvent::Started, this, &ATekuaniMarcelaCharacter::HandleShootInput);
	}
}

void ATekuaniMarcelaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DirectionComponent->OnDirectionChanged.AddDynamic(this, &ATekuaniMarcelaCharacter::OnDirectionChanged);
	
	// Apply vertical pitch constraints to maintain cinematic framing.
	// Prevents disorienting camera angles and preserves level composition.
	if (APlayerController* MarcelaPlayerController = Cast<APlayerController>(GetController()))
	{
		if (APlayerCameraManager* CameraManager = MarcelaPlayerController->PlayerCameraManager)
		{
			CameraManager->ViewPitchMin = -20.f;
			CameraManager->ViewPitchMax = 20.f;
		}
	}
}

void ATekuaniMarcelaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DirectionComponent->UpdateDirection(this);
}

void ATekuaniMarcelaCharacter::InitializeCamera()
{
	// Create Spring Arm (Camera Boom)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	// 500 units chosen to maintain consistent spatial readability
	// for medium-scale combat and traversal scenarios.
	CameraBoom->TargetArmLength = 500.0f;

	// Offset tuned to improve character framing in 2.5D perspective.
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);

	// Allows controller input to rotate the camera boom.
	CameraBoom->bUsePawnControlRotation = true;

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Camera rotation handled by spring arm, not directly by pawn.
	FollowCamera->bUsePawnControlRotation = false;
	
	/** ===== CAMERA COMPONENT ===== */
	MarcelaCameraComponent = CreateDefaultSubobject<UMarcelaCameraComponent>("MarcelaCameraComponent");
}

void ATekuaniMarcelaCharacter::ConfigureMovement()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();

	// Disable automatic rotation toward movement direction.
	// Rotation behavior may later be driven by custom logic or GAS.
	Movement->bOrientRotationToMovement = false;

	// High Z rotation rate for responsive lateral direction changes.
	Movement->RotationRate = FRotator(0.f, 36000.f, 0.f);

	// Default walk speed tuned for responsive gameplay feel.
	Movement->MaxWalkSpeed = 600.0f;

	// Braking tuned for tighter stopping control.
	Movement->BrakingDecelerationWalking = 2000.f;
}

void ATekuaniMarcelaCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	
	// Movement Input Only
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATekuaniMarcelaCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
		AddControllerYawInput(LookAxisVector.X);
	
	if (LookAxisVector.Y != 0.f)
		AddControllerPitchInput(LookAxisVector.Y * -1.f);
}

void ATekuaniMarcelaCharacter::Input_AbilityInputPressed(FGameplayTag InInputValue)
{
	TekuaniAbilitySystemComponent->OnAbilityInputPressed(InInputValue);
}

void ATekuaniMarcelaCharacter::Input_AbilityInputReleased(FGameplayTag InInputValue)
{
	TekuaniAbilitySystemComponent->OnAbilityInputReleased(InInputValue);
}

void ATekuaniMarcelaCharacter::HandleAimInput(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
		MarcelaCombatComponent->StartAiming();
	else 
		MarcelaCombatComponent->StopAiming();
}

void ATekuaniMarcelaCharacter::HandleShootInput(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
		MarcelaCombatComponent->TryShoot();
}

UPaperZDAnimInstance* ATekuaniMarcelaCharacter::GetMarcelaAnimBPComponent()
{
	return GetAnimationComponent()->GetAnimInstance();
}

void ATekuaniMarcelaCharacter::OnDirectionChanged(EMarcelaDirection NewDirection)
{
	if (!WeaponSocket) return;

	switch (NewDirection)
	{
	case EMarcelaDirection::Front:
		WeaponSocket->SetRelativeLocation(FVector(0.f, -10.f, 0.f));
		break;

	case EMarcelaDirection::Back:
		WeaponSocket->SetRelativeLocation(FVector(0.f, 10.f, 0.f));
		break;

	case EMarcelaDirection::Right:
		WeaponSocket->SetRelativeLocation(FVector(-5.f, 10.f, 0.f));
		break;

	case EMarcelaDirection::Left:
		WeaponSocket->SetRelativeLocation(FVector(5.f, 10.f, 0.f));
		break;
	}
}

/* DATA-DRIVEN VERSION
void ATekuaniMarcelaCharacter::OnDirectionChanged(EMarcelaDirection NewDirection)
{
	if (!WeaponSocket || !CurrentWeaponDefinition) return;

	if (!CurrentWeaponDefinition->OffsetData) return;

	const FWeaponDirectionalOffset& Offset =
		CurrentWeaponDefinition->OffsetData->OffsetData;

	FVector NewOffset = FVector::ZeroVector;

	switch (NewDirection)
	{
	case EMarcelaDirection::Front:
		NewOffset = Offset.Front;
		break;

	case EMarcelaDirection::Back:
		NewOffset = Offset.Back;
		break;

	case EMarcelaDirection::Right:
		NewOffset = Offset.Right;
		break;

	case EMarcelaDirection::Left:
		NewOffset = Offset.Left;
		break;
	}

	WeaponSocket->SetRelativeLocation(NewOffset);
}
*/