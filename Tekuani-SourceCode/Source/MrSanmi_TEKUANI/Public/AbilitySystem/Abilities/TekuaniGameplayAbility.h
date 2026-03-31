// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TekuaniGameplayAbility.generated.h"

class UPawnCombatComponent;
class UTekuaniAbilitySystemComponent;

/**
 * @enum ETekuaniAbilityActivationPolicy
 * @brief Defines when a gameplay ability should automatically activate.
 *
 * This policy determines the lifecycle behavior of abilities
 * when granted to an Ability System Component.
 *
 * Design Intent:
 * - Allow flexible activation behavior without duplicating logic.
 * - Support passive or one-shot abilities triggered immediately on grant.
 */
UENUM(BlueprintType)
enum class ETekuaniAbilityActivationPolicy : uint8
{
	/** Ability activates only when explicity triggered by input or event. */
	OnTriggered,
	
	/** Ability automatically activates immediately when granted. */
	OnGiven
};

/**
 * @class UTekuaniGameplayAbility
 * @brief Base gameplay ability class for Tekuani built on top of GAS.
 *
 * Extends UGameplayAbility to introduce custom activation policies
 * tailored to Tekuani's combat architecture.
 *
 * Architectural Role:
 * - Centralizes activation behavior logic.
 * - Enables automatic execution of specific abilities when granted.
 * - Serves as base class for all concrete GA_ abilities.
 *
 * Design Intent:
 * - Reduce repetitive activation logic in derived abilities.
 * - Allow passive, temporary, or instant abilities (buffs, effects, etc.)
 *   to execute immediately upon being granted.
 *
 * Notes:
 * - Designed to integrate with TekuaniAbilitySystemComponent.
 * - Abilities marked as OnGiven will self-clear after execution.
 */
UCLASS()
class MRSANMI_TEKUANI_API UTekuaniGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface.
	
	/**
	 * @brief Called when the ability is granted to an actor.
	 *
	 * If the activation policy is set to OnGiven,
	 * the ability attempts immediate activation.
	 *
	 * @param ActorInfo Context information about the owning actor.
	 * @param Spec Ability specification containing runtime data.
	 */
	virtual void OnGiveAbility(
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilitySpec& Spec) override;
	
	/**
	 * @brief Ends the ability execution.
	 *
	 * If the ability was configured as OnGiven,
	 * it is cleared from the Ability System after finishing.
	 *
	 * @param Handle Unique handle identifying this ability instance.
	 * @param ActorInfo Context information about the owning actor.
	 * @param ActivationInfo Data related to how the ability was activated.
	 * @param bReplicateEndAbility Whether to replicate the end to clients.
	 * @param bWasCancelled Whether the ability ended due to cancellation.
	 */
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;
	
	//~ End UGameplayAbility Interface.
	
	/**
	 * @brief Determines when the ability should activate.
	 *
	 * Gameplay Impact:
	 * - OnTriggered → standard input/event-driven ability.
	 * - OnGiven → auto-activated and self-clearing ability.
	 *
	 * This allows implementation of:
	 * - Instant buffs
	 * - Temporary effects
	 * - Auto-triggered passives
	 */
	UPROPERTY(EditDefaultsOnly, Category = "TekuaniAbility")
	ETekuaniAbilityActivationPolicy AbilityActivationPolicy { ETekuaniAbilityActivationPolicy::OnTriggered };
	
	UFUNCTION(BlueprintPure, Category = "Tekuani|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Tekuani|Ability")
	UTekuaniAbilitySystemComponent* GetTekuaniAbilitySystemComponentFromActorInfo() const;
};
