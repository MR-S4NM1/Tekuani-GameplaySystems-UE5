// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/Lore/TekuaniLoreBaseCharacter.h"
#include "TekuaniMarcelaLoreCharacter.generated.h"

#pragma region Enums

/**
 * @enum EMarcelaLoreState
 * @brief Defines the high-level behavioral state of Marcela during lore/town gameplay.
 *
 * This state is primarily used to control animation transitions and
 * restrict certain inputs while interacting with world elements.
 */
UENUM(BlueprintType)
enum class EMarcelaLoreState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA(DisplayName = "Moving"),
	Interacting UMETA(DisplayName = "Interacting"),
};
#pragma endregion Enums

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

/**
 * @class ATekuaniMarcelaLoreCharacter
 * @brief Player-controlled version of Marcela used in town/lore environments.
 *
 * This class represents the exploration-only version of Marcela used in
 * narrative areas such as towns, hubs, and dialogue-driven locations.
 *
 * Responsibilities:
 * - Process player input for movement and interaction.
 * - Configure the exploration camera system.
 * - Detect interactable actors in the environment.
 *
 * Design Intent:
 * - Keep exploration gameplay lightweight and separated from combat systems.
 * - Avoid loading combat-related components while in lore areas.
 * - Provide a clean interaction layer for dialogue and narrative triggers.
 */
UCLASS(Blueprintable)
class MRSANMI_TEKUANI_API ATekuaniMarcelaLoreCharacter : public ATekuaniLoreBaseCharacter
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Default constructor.
	 *
	 * Initializes the exploration camera and movement configuration.
	 */
	ATekuaniMarcelaLoreCharacter();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	/**
	 * @brief Called when the actor enters the game world.
	 *
	 * Registers overlap events used to detect interactable actors.
	 */
	virtual void BeginPlay() override;
	
	/**
	 * @brief Handles player movement input.
	 *
	 * @param Value 2D vector representing movement direction.
	 */
	UFUNCTION()
	void MoveEnhanced(const FInputActionValue& Value);
	
	/**
	 * @brief Handles interaction input from the player.
	 *
	 * Attempts to trigger interaction on the currently detected interactable actor.
	 */
	UFUNCTION()
	void InteractEnhanced(const FInputActionValue& Value);
	
	/**
	 * @brief Triggered when Marcela begins overlapping another actor.
	 *
	 * Used to detect actors that implement the interaction interface.
	 */
	UFUNCTION()
	void OnLoreMarcelaBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
	
	/**
	 * @brief Triggered when Marcela stops overlapping another actor.
	 *
	 * Clears the currently stored interactable reference if necessary.
	 */
	UFUNCTION()
	void OnLoreMarcelaEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	/** Initializes the exploration camera setup. */
	void InitializeCamera();
	
	/** Configures movement parameters for exploration gameplay. */
	void ConfigureMovement();

private:
	/** Camera used during exploration gameplay. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* LoreMarcelaCamera;
	
	/** Spring arm controlling camera distance and offset. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* LoreMarcelaCameraBoom;
	
	/**
	 * Actor currently available for interaction.
	 *
	 * Stored when the player overlaps an actor implementing
	 * the interaction interface.
	 */
	UPROPERTY()
	AActor* CurrentInteractableActor { nullptr };
	
protected:
	/** Current exploration state of Marcela. */
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EMarcelaLoreState CurrentLoreState { EMarcelaLoreState::Idle };
	
	/** Input mapping context used during exploration gameplay. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* LoreMappingContext;
	
	/** Input action for character movement. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	
	/** Input action for interacting with world objects. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;
	
	/** Input action used for jumping. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;
};
