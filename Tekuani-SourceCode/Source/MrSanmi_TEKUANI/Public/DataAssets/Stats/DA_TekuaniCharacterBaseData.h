// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Structs/TekuaniCharacterStats.h"
#include "DA_TekuaniCharacterBaseData.generated.h"

/**
 * @class UDA_TekuaniCharacterBaseData
 * @brief Data Asset containing base stats for any character.
 *
 * Design Intent:
 * - Centralize character stat tuning (player, enemies, party).
 * - Enable data-driven balancing without recompilation.
 * - Serve as the foundation for progression, scaling, and difficulty adjustments.
 *
 * Notes:
 * - This asset is read-only at runtime.
 * - Runtime modifications should be handled via components (Combat, Progression, etc.).
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniCharacterBaseData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** Character identifier (for debugging / UI) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	FName CharacterName;
	
	/** Base stats for this character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FTekuaniCharacterStats CharacterStats;
	
	/** Gameplay Tag */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	FGameplayTag CharacterTag;
};
