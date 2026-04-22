// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/TekuaniWeaponRecoilData.h"
#include "DA_TekuaniWeaponRecoil.generated.h"

/**
 * @class UDA_TekuaniWeaponRecoil
 * @brief Data Asset for weapon recoil configuration.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniWeaponRecoil : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponRecoilData RecoilData;
};
