// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "AbilitySystem/Abilities/StateAbilities/GA_Tekuani_Stagger.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TekuaniGameplayTags.h"

UGA_Tekuani_Stagger::UGA_Tekuani_Stagger()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	ActivationOwnedTags.AddTag(TekuaniGameplayTags::Player_State_Staggered);
}

void UGA_Tekuani_Stagger::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// Blocks movement
	Character->GetCharacterMovement()->DisableMovement();
	
	// Timer (PaperZD does not use montages as commonly used)
	FTimerHandle TimerHandle;
	
	Character->GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this, Handle, ActorInfo, ActivationInfo]()
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		},
		StaggerDuration,
		false
		);
	
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.0f,
	FColor::Red,
	TEXT("STAGGER ACTIVATED"));
}

void UGA_Tekuani_Stagger::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	
	if (Character)
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.0f,
	FColor::Red,
	TEXT("STAGGER ENDED"));
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

