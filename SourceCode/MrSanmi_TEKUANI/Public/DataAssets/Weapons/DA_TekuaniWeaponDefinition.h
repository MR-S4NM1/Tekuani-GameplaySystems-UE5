// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_TekuaniWeaponBaseData.h"
#include "DA_TekuaniWeaponFireModes.h"
#include "DA_TekuaniWeaponOffset.h"
#include "DA_TekuaniWeaponRecoil.h"
#include "DA_TekuaniWeaponSway.h"
#include "DA_TekuaniWeaponDefinition.generated.h"

/**
 * @class UDA_TekuaniWeaponDefinition
 * @brief Master definition for a weapon.
 *
 * Design Intent:
 * - Centralize all weapon-related data.
 * - Provide a single access point for gameplay systems (Combat, GAS, UI).
 * - Keep system fully data-driven and modular.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	UDA_TekuaniWeaponBaseData* BaseData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	UDA_TekuaniWeaponFireModes* FireModesData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	UDA_TekuaniWeaponRecoil* RecoilData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	UDA_TekuaniWeaponSway* SwayData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	UDA_TekuaniWeaponOffset* OffsetData;
};
