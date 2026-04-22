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
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Weapon|FireMode")
	int32 GetCurrentFireModeIndex() const { return CurrentFireModeIndex; }
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Weapon|FireMode")
	void SetCurrentFireModeIndex(int32 NewIndex) { CurrentFireModeIndex = NewIndex; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|State")
	int32 CurrentFireModeIndex = 0;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
