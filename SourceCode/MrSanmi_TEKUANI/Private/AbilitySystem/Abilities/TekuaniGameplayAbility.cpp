// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UTekuaniGameplayAbility::OnGiveAbility(
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	/**
	 * If the ability is configured as OnGiven,
	 * it should activate immediately upon being granted.
	 *
	 * This supports instant gameplay effects such as:
	 * - Temporary buffs
	 * - One-shot triggered abilities
	 * - Automatic passive initialization
	 *
	 * Safety check ensures:
	 * - ActorInfo is valid
	 * - Ability is not already active
	 */
	if (AbilityActivationPolicy == ETekuaniAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UTekuaniGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	/**
	 * Abilities configured as OnGiven are considered
	 * temporary or single-execution abilities.
	 *
	 * Once finished, they remove themselves from the
	 * Ability System to prevent unintended reuse.
	 *
	 * This enforces a clean lifecycle for:
	 * - Buff applications
	 * - Instant gameplay effects
	 * - Event-driven temporary abilities
	 */
	if (AbilityActivationPolicy == ETekuaniAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UTekuaniGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UTekuaniAbilitySystemComponent* UTekuaniGameplayAbility::GetTekuaniAbilitySystemComponentFromActorInfo() const
{
	return Cast<UTekuaniAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}