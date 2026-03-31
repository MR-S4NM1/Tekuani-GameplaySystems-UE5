// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/TekuaniBaseCharacter.h"
#include "TekuaniMarcelaCharacter.generated.h"

class UMarcelaDirectionComponent;
class UInputMappingContext;
class UInputAction;
class UPaperFlipbookComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
class UMarcelaCombatComponent;
class UMarcelaCameraComponent;

#pragma region Enum

UENUM(BlueprintType)
enum EMarcela_CorporalPosture:uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Revolver UMETA(DisplayName = "Revolver"),
	Pistol UMETA(DisplayName = "Pistol"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
	FragGrenade UMETA(DisplayName = "Frag Grenade"),
	EMPGrenade UMETA(DisplayName = "EMP Grenade"),
	SubmachineGun UMETA(DisplayName = "Submachine Gun"),
	SniperRifle UMETA(DisplayName = "Sniper Rifle")
};

UENUM(BlueprintType)
enum class EMarcelaDirection : uint8
{
	Front,
	Back,
	Left,
	Right
};

#pragma endregion

/**
 * @class ATekuaniMarcelaCharacter
 * @brief Main playable character implementation for Marcela.
 *
 * Extends ATekuaniBaseCharacter and defines:
 * - Camera system (Spring Arm + Follow Camera)
 * - Default movement configuration
 * - Runtime camera pitch constraints
 *
 * Design Goals:
 * - Maintain clean camera framing for 2.5D gameplay
 * - Prevent extreme pitch rotation to preserve composition
 * - Keep rotation control decoupled from controller yaw
 */
UCLASS()
class MRSANMI_TEKUANI_API ATekuaniMarcelaCharacter : public ATekuaniBaseCharacter
{
	GENERATED_BODY()
	
public:
	/**
	 * Default constructor.
	 * Initializes camera components and movement configuration.
	 */
	ATekuaniMarcelaCharacter();
	
	
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/**
	 * Called when the game starts or when spawned.
	 * Used here to configure runtime camera pitch constraints.
	 */
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
private:
#pragma region Components
	/**
	 * @brief Spring arm responsible for camera positioning and smoothing.
	 *
	 * Handles:
	 * - Camera distance
	 * - Rotation inheritance
	 * - Framing offset
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	/**
	 * @brief Player follow camera.
	 *
	 * Attached to the spring arm socket.
	 * Does not inherit direct pawn control rotation.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UMarcelaCombatComponent* MarcelaCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UMarcelaCameraComponent* MarcelaCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Direction", meta=(AllowPrivateAccess="true"))
	UMarcelaDirectionComponent* DirectionComponent;
	
#pragma endregion
	
#pragma region Initialization

	/** Initializes camera-related components and settings. */
	void InitializeCamera();
	
	/** Configures default movement parameters. */
	void ConfigureMovement();

#pragma endregion

#pragma region Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputPressed(FGameplayTag InInputValue);
	void Input_AbilityInputReleased(FGameplayTag InInputValue);
	
#pragma region Special Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AimAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ShootAction;
	
	UFUNCTION()
	void HandleAimInput(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleShootInput(const FInputActionValue& Value);
	
#pragma endregion 

#pragma endregion
	
	/* The would-be Data-Driven implementation
	 *UPROPERTY(EditDefaultsOnly, Category = "Offset")
	TMap<EMarcelaDirection, FVector> DirectionalOffsets;*/
	
#pragma region GettersAndSetters
	
public:
	FORCEINLINE UMarcelaCombatComponent* GetMarcelaCombatComponent() const { return MarcelaCombatComponent; }
	
	UFUNCTION(BlueprintCallable)
	UPaperZDAnimInstance* GetMarcelaAnimBPComponent();
	
#pragma endregion 
	
#pragma region EnumState
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TEnumAsByte<EMarcela_CorporalPosture> CurrentState;
	
#pragma endregion
	
#pragma region Events
	
	UFUNCTION()
	void OnDirectionChanged(EMarcelaDirection NewDirection);
	
#pragma endregion
};
