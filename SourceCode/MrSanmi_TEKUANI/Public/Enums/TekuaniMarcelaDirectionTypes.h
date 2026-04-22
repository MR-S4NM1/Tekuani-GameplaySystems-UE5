// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniMarcelaDirectionTypes.generated.h"

UENUM(BlueprintType)
enum class EMarcelaDirection : uint8
{
	Front,
	Back,
	Left,
	Right
};