// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TekuaniTypes/TekuaniStructTypes.h"
#include "TekuaniAbilitySystemComponent.generated.h"

class ATekuaniMarcelaCharacter;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UTekuaniAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(
		const TArray<FTekuaniMarcelaAbilitySet>& InDefaultWeaponAbilities, 
		int32 ApplyLevel,
		TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Ability")
	void RemoveGrantedMarcelaWeaponAbilities(
	UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};
