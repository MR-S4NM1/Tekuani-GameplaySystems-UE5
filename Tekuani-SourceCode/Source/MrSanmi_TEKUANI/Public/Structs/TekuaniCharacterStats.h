// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniCharacterStats.generated.h"

USTRUCT(BlueprintType)
struct FTekuaniCharacterStats
{
	GENERATED_BODY()
	
	/** Level scaling */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Level = 1;
    
	/** Maximum health of the character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHealth = 100.f;
    
	/** Base attack power */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Attack = 10.f;
    
	/** Defense used for damage mitigation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Defense = 10.f;
    
	/** Movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MovementSpeed = 600.f;
    
	/** Cooldown reduction (0–1 range) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Haste = 0.f;
};
