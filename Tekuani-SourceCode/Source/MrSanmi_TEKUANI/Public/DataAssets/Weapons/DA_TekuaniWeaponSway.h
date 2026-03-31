// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/TekuaniWeaponSwayData.h"
#include "DA_TekuaniWeaponSway.generated.h"

/**
 * @class UDA_TekuaniWeaponSway
 * @brief Data Asset for weapon sway configuration.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponSway : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponSwayData SwayData;
};
