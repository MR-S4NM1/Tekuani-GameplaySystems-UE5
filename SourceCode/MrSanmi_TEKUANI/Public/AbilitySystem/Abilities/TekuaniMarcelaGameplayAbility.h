// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"
#include "TekuaniMarcelaGameplayAbility.generated.h"

class UMarcelaCombatComponent;
class ATekuaniMarcelaController;
class ATekuaniMarcelaCharacter;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UTekuaniMarcelaGameplayAbility : public UTekuaniGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Tekuani|Ability")
	ATekuaniMarcelaCharacter* GetMarcelaCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Tekuani|Ability")
	ATekuaniMarcelaController* GetMarcelaControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Tekuani|Ability")
	UMarcelaCombatComponent* GetMarcelaCombatComponentFromActorInfo();
	
private:
	TWeakObjectPtr<ATekuaniMarcelaCharacter> CachedTekuaniMarcelaCharacter;
	TWeakObjectPtr<ATekuaniMarcelaController> CachedTekuaniMarcelaController;
	
};