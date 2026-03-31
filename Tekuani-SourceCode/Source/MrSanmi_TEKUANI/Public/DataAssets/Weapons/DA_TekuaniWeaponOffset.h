// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/TekuaniWeaponDirectionalOffset.h"
#include "DA_TekuaniWeaponOffset.generated.h"

/**
 * @class UDA_TekuaniWeaponOffset
 * @brief Data Asset for weapon directional offsets.
 *
 * Design Intent:
 * - Decouple weapon visuals from code.
 * - Allow designers to tweak offsets per weapon.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponOffset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Offset")
	FTekuaniWeaponDirectionalOffset OffsetData;
};
