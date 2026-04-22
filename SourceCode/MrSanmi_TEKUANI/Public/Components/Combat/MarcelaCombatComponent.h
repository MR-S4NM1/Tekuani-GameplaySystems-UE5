// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "DataAssets/Weapons/DA_TekuaniWeaponDefinition.h"
#include "MarcelaCombatComponent.generated.h"

class UMarcelaCameraComponent;
class ATekuaniMarcelaController;
class ATekuaniMarcelaWeapon;
class ATekuaniMarcelaCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponFired, float, RecoilAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingChanged, bool, bIsAiming);

/**
 * @class UMarcelaCombatComponent
 * @brief Handles Marcela-specific combat logic including aiming and shooting.
 *
 * This component extends UPawnCombatComponent to provide player-exclusive
 * combat behavior for Marcela.
 *
 * Responsibilities:
 * - Manage aiming state.
 * - Handle shooting input validation.
 * - Perform hit detection via raycasting.
 * - Serve as bridge between input (Character) and weapon logic.
 *
 * Architectural Role:
 * - Acts as the core combat controller for the player character.
 * - Delegates weapon-specific behavior to ATekuaniMarcelaWeapon.
 * - Keeps the Character class clean and input-focused.
 *
 * Design Intent:
 * - Centralize all combat state (aiming, shooting conditions).
 * - Prepare system for data-driven weapon behavior.
 * - Ensure scalability for multiple weapon types and fire modes.
 *
 * Notes:
 * - Does NOT handle damage calculation directly (delegated to weapon or damage system).
 * - Raycast logic is temporary and may later be abstracted into a targeting system.
 */
UCLASS()
class MRSANMI_TEKUANI_API UMarcelaCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	/** Initializes cached references for optimized runtime access. */
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UMarcelaCombatComponent();
	
	/**
     * @brief Retrieves the currently carried weapon matching a gameplay tag.
     *
     * @param InWeaponTag Tag used to identify the weapon.
     * @return Pointer to Marcela-specific weapon instance, or nullptr if not found.
     */
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	ATekuaniMarcelaWeapon* GetMarcelaCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tekuani|Combat")
	UDA_TekuaniWeaponDefinition* CurrentWeaponDefinition;

	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	UDA_TekuaniWeaponDefinition* GetCurrentWeaponDefinition() const { return CurrentWeaponDefinition; }
	
#pragma region Shooting System
	
	/** Activates aiming state. */
	UFUNCTION(BlueprintCallable)
	void StartAiming();
	
	/** Deactivates aiming state. */
	UFUNCTION(BlueprintCallable)
	void StopAiming();
	
	/** Changes to the next available fire mode of the current weapon */
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	void CycleFireMode();
	
	/**
	 * @brief Applies immediate recoil kick and accumulates recoil for recovery.
	 *
	 * This function is responsible for the "instant feedback" when firing.
	 * It applies a direct camera input offset to simulate weapon kick,
	 * ensuring that each shot feels impactful and responsive.
	 *
	 * Additionally, it accumulates recoil into TargetRecoil, which will be
	 * gradually recovered over time in UpdateRecoil().
	 *
	 * Design Notes:
	 * - Immediate input ensures responsiveness (no interpolation delay).
	 * - Accumulation enables sustained fire penalty.
	 * - Recoil is affected by RecoilControl (progression system).
	 *
	 */
	void ApplyRecoil(FWeaponRecoilData& RecoilData);
	
	/**
	 * @brief Returns current aiming state.
	 *
	 * @return True if the character is currently aiming.
	 */
	bool IsAiming() const;
	
private:
	
	/**
	 * @brief Smoothly recovers recoil over time and applies camera correction.
	 *
	 * This function handles the recovery phase of the recoil system.
	 * It interpolates TargetRecoil back to zero and makes CurrentRecoil
	 * follow it smoothly to create a natural camera return effect.
	 *
	 * Instead of applying absolute values, it applies the delta between frames,
	 * preventing jitter and ensuring stable camera behavior.
	 *
	 * Design Notes:
	 * - Separation of TargetRecoil and CurrentRecoil allows fine control
	 *   between "gameplay recoil" and "visual smoothing".
	 * - Delta-based application avoids cumulative floating-point drift.
	 * - Recovery speed is controlled via RecoilReturnSpeed.
	 * - Smoothness is controlled via RecoilDamping.
	 *
	 * Gameplay Impact:
	 * - Enables skill-based recoil control.
	 * - Punishes sustained fire without control.
	 * - Supports future extensions (weapon patterns, curves, modifiers).
	 *
	 * @param DeltaTime Time elapsed since last frame.
	 */
	void UpdateRecoil(float DeltaTime);
	
private:
	/** Indicates whether the player is currently aiming. */
	bool bIsAiming {false};
	
	/**
	 * Cached reference to owning pawn for performance optimization.
	 * Avoids repeated casting during gameplay-critical functions.
	 */
	TWeakObjectPtr<APawn> CachedPawn;
	
#pragma region Recoil

	/** Base vertical recoil applied per shot */
	UPROPERTY(EditAnywhere, Category = "Recoil", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
	float RecoilPitch = 2.0f ;

	/** Max horizontal recoil variation */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilYawRange = 0.5f;

	/** How fast recoil returns to center */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilReturnSpeed = 6.0f;

	/** How smooth the recoil interpolation feels */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilDamping = 12.0f;

	/** Progression factor (0 = worst, 1 = perfect aim) */
	UPROPERTY(EditAnywhere, Category = "Recoil", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RecoilControl = 0.0f;
	
	FVector2D TargetRecoil = FVector2D::ZeroVector;
	FVector2D CurrentRecoil = FVector2D::ZeroVector;
	FVector2D LastFrameRecoil = FVector2D::ZeroVector;
	
#pragma endregion
	
#pragma region Sway
	UPROPERTY(VisibleAnywhere)
	ATekuaniMarcelaCharacter* MarcelaCharacter;
	
	UPROPERTY(VisibleAnywhere)
	ATekuaniMarcelaController* MarcelaController;
	
	UPROPERTY(VisibleAnywhere)
	UMarcelaCameraComponent* MarcelaCameraComponent;
	
#pragma endregion
	
#pragma endregion
	
#pragma region Events
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFired OnWeaponFired;

	UPROPERTY(BlueprintAssignable)
	FOnAimingChanged OnAimingChanged;
	
#pragma endregion Events
};
