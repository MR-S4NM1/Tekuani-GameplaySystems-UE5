// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/TekuaniMarcelaDirectionTypes.h"
#include "MarcelaDirectionComponent.generated.h"

class ACharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectionChanged, EMarcelaDirection, NewDirection);

/**
 * @class UMarcelaDirectionComponent
 * @brief Handles directional state logic for Marcela based on movement and camera orientation.
 *
 * This component determines the facing direction of the character (Front, Back, Left, Right)
 * using the character's velocity and control rotation.
 *
 * Responsibilities:
 * - Evaluate movement direction relative to camera orientation.
 * - Maintain a consistent directional state.
 * - Notify other systems (animation, weapon positioning) when direction changes.
 *
 * Architectural Role:
 * - Acts as the single source of truth for direction.
 * - Decouples gameplay logic from animation (PaperZD).
 * - Broadcasts direction changes via delegates.
 *
 * Notes:
 * - Direction is computed using velocity, not raw input.
 * - Avoids redundant updates by only broadcasting on change.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRSANMI_TEKUANI_API UMarcelaDirectionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	/** Default constructor. Disables ticking (driven externally by owner). */
	UMarcelaDirectionComponent();

	virtual void BeginPlay() override;

	/**
	 * @brief Updates the current direction based on movement and control rotation.
	 *
	 * @param OwnerCharacter Character that owns this component.
	 *
	 * This function:
	 * - Retrieves velocity and flattens it to XY plane.
	 * - Uses control rotation (yaw) to compute forward/right vectors.
	 * - Determines dominant axis via dot product.
	 * - Updates direction only if it changes.
	 */
	void UpdateDirection(ACharacter* OwnerCharacter);

	/**
	 * @brief Converts current direction to a 2D vector for animation systems.
	 *
	 * @return FVector2D Direction vector used by PaperZD.
	 */
	UFUNCTION(BlueprintCallable)
	FVector2D GetDirectionForAnim() const;

	/**
	 * @brief Returns the current directional state.
	 */
	UFUNCTION(BlueprintPure)
	FORCEINLINE EMarcelaDirection GetCurrentDirection() const { return CurrentDirection; }

public:
	/** Broadcast when direction changes. */
	UPROPERTY(BlueprintAssignable)
	FOnDirectionChanged OnDirectionChanged;

private:
	/**
	 * @brief Current direction state used across gameplay and animation systems.
	 *
	 * This variable represents the authoritative facing direction of Marcela.
	 */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	EMarcelaDirection CurrentDirection = EMarcelaDirection::Front;
};
