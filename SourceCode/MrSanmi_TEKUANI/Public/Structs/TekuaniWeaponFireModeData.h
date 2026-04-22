// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Enums/TekuaniWeaponFireMode.h"
#include "TekuaniWeaponFireModeData.generated.h"

/**
 * @struct FTekuaniWeaponFireModeData
 * @brief Defines behavior for a specific fire mode.
 */
USTRUCT(BlueprintType)
struct FTekuaniWeaponFireModeData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETekuaniWeaponFireMode FireMode;

	// RPM o velocidad específica de este modo
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate { 600.f };

	// Solo relevante para burst
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 BurstCount { 3 };
};
