// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "DA_TekuaniWeaponBaseData.generated.h"

/**
 * @struct FWeaponBaseStats
 * @brief Core gameplay stats for a weapon.
 *
 * This struct defines the fundamental combat behavior of a weapon.
 * Used for data-driven balancing without recompilation.
 */
USTRUCT(BlueprintType)
struct FWeaponBaseStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UGameplayEffect> DamageEffect = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float FireRate = 600.f; // RPM

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ReloadSpeed = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float Range = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 MagazineSize = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 MaxAmmo = 120;
};

/**
 * @class UDA_TekuaniWeaponBaseData
 * @brief Data Asset containing base weapon stats.
 *
 * Design Intent:
 * - Centralize weapon tuning values.
 * - Allow designers to tweak combat without touching code.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponBaseData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FGameplayTag WeaponTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FWeaponBaseStats BaseStats;
};
