// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniWeaponFireMode.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETekuaniWeaponFireMode : uint8
{
	SemiAuto UMETA(DisplayName = "Semi Auto"),
	FullAuto UMETA(DisplayName = "Full Auto"),
	Burst UMETA(DisplayName = "Burst")
};