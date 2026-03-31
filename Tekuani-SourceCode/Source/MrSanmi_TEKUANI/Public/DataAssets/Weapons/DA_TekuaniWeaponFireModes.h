// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/TekuaniWeaponFireModeData.h"
#include "DA_TekuaniWeaponFireModes.generated.h"

/**
 * @class UDA_TekuaniWeaponFireModes
 * @brief Defines all available fire modes for a weapon.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponFireModes : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTekuaniWeaponFireModeData> AvailableFireModes;
};
