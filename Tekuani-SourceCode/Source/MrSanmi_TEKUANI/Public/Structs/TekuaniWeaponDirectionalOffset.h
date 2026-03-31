// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniWeaponDirectionalOffset.generated.h"

/**
 * @struct FTekuaniWeaponDirectionalOffset
 * @brief Defines weapon offset per facing direction.
 *
 * Design Intent:
 * - Allow per-weapon customization of visual alignment.
 * - Fully data-driven without code changes.
 */
USTRUCT(BlueprintType)
struct FTekuaniWeaponDirectionalOffset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Offset")
	FVector Front { FVector::ZeroVector };

	UPROPERTY(EditDefaultsOnly, Category = "Offset")
	FVector Back { FVector::ZeroVector };

	UPROPERTY(EditDefaultsOnly, Category = "Offset")
	FVector Right { FVector::ZeroVector };

	UPROPERTY(EditDefaultsOnly, Category = "Offset")
	FVector Left { FVector::ZeroVector };
};