// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniStatModifierType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETekuaniStatsModifier : uint8
{
	Instant UMETA(DisplayName = "Instant Effect"),
	OverTime UMETA(DisplayName = "Over Time Effect"),
	CrowdControl UMETA(DisplayName = "Crowd Control Effect")
};