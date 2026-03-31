// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/TekuaniWeaponBase.h"
#include "TekuaniTypes/TekuaniStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "TekuaniMarcelaWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API ATekuaniMarcelaWeapon : public ATekuaniWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FTekuaniMarcelaWeaponData MarcelaWeaponData;
	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
