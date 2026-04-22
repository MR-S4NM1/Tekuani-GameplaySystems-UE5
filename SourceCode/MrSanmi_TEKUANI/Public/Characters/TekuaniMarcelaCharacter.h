// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/TekuaniBaseCharacter.h"
#include "Enums/TekuaniMarcelaDirectionTypes.h"
#include "ActiveGameplayEffectHandle.h"
#include "TekuaniMarcelaCharacter.generated.h"

class UTekuaniInventoryComponent;
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
	
	virtual void BindDelegates() override;
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
	UMarcelaDirectionComponent* DirectionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Inventory", meta = (AllowPrivateAccess = "true"))
	UTekuaniInventoryComponent* InventoryComponent;
	
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
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_RightStickSpecialAction(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputPressed(FGameplayTag InInputValue);
	void Input_AbilityInputReleased(FGameplayTag InInputValue);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer BlockedTags;
	
#pragma region Special Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AimAction;
	
	UFUNCTION()
	void SetAimInput(const FInputActionValue& Value);
	
#pragma endregion 

#pragma endregion
	
#pragma region GettersAndSetters
	
public:
	FORCEINLINE UMarcelaCombatComponent* GetMarcelaCombatComponent() const { return MarcelaCombatComponent; }
	
	FORCEINLINE UTekuaniInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	
	UFUNCTION(BlueprintCallable)
	UPaperZDAnimInstance* GetMarcelaAnimBPComponent();
	
	UFUNCTION(BlueprintPure)
	FVector2D GetLastInputMove() const { return LastInputMove; }
	
#pragma endregion 
	
#pragma region Runtime Variables
	
	UPROPERTY(BlueprintReadOnly, Category = "Input|Info")
	FVector2D LastInputMove = FVector2D::ZeroVector;
	
#pragma endregion Runtime Variables
	
#pragma region EnumState
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TEnumAsByte<EMarcela_CorporalPosture> CurrentState;
	
#pragma endregion
	
#pragma region Events
	
	UFUNCTION()
	void OnDirectionChanged(EMarcelaDirection NewDirection);
#pragma endregion
	
#pragma region GAS Progression
public:
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Progression")
	void OnMilestoneReached(int32 NewLevel);
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Progression")
	void UpdatePassiveRegeneration(int32 NewMilestoneLevel);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Effects")
	TSubclassOf<class UGameplayEffect> InitStatsEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Effects")
	TSubclassOf<class UGameplayEffect> PassiveRegenEffectClass;

	FActiveGameplayEffectHandle ActivePassiveRegenHandle;
	
#pragma endregion
	
#pragma region Debug & Test Functions
	
	UFUNCTION(BlueprintCallable)
	void TestStagger();
	
	
#pragma endregion Debug & Test Functions
};
