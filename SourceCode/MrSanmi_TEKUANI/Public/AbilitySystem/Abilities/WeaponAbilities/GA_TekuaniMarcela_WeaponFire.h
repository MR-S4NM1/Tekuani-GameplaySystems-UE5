// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TekuaniMarcelaGameplayAbility.h"
#include "GA_TekuaniMarcela_WeaponFire.generated.h"

/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UGA_TekuaniMarcela_WeaponFire : public UTekuaniMarcelaGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_TekuaniMarcela_WeaponFire();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	/** Helper function to execute the raycast logic */
	void PerformHitscan();
	
	// --- Fire Modes Logic (Tasks Callbacks) ---
	
	UFUNCTION()
	void OnInputReleased(float TimeHeld);
	
	UFUNCTION()
	void FireFullAutoLoop();
	
	UFUNCTION()
	void FireBurstLoop();
	
private:
	// Burst Variables
	int32 BurstShotsFired = 0;
	int32 MaxBurstShots = 3;
	float BurstDelay = 0.1f;
};
