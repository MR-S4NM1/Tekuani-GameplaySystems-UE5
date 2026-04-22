// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class ATekuaniWeaponBase;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	void RegisterSpawnedWeapon(
		FGameplayTag InWeaponTagToRegister,
		ATekuaniWeaponBase* InWeaponToRegister, 
		bool bRegisterAsEquippedWeapon = false
		);
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	ATekuaniWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Tekuani|Combat")
	ATekuaniWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UPROPERTY(BlueprintReadWrite, Category = "Tekuani|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
private:
	TMap<FGameplayTag, ATekuaniWeaponBase*> CharacterCarriedWeaponMap;
};