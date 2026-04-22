// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"
#include "GA_Tekuani_Stagger.generated.h"

/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UGA_Tekuani_Stagger : public UTekuaniGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Tekuani_Stagger();
	
protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Stagger")
	float StaggerDuration = 2.f;
};
