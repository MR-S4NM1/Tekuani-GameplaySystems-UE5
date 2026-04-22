// // Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "TekuaniCharacterStats.h"
// #include "Enums/TekuaniStatModifierType.h"
// #include "TekuaniStatusEffect.generated.h"
//
// /**
//  * 
//  */
// USTRUCT(BlueprintType)
// struct FActiveStatModifier
// {
// 	GENERATED_BODY()
// 	
// 	/** Unique identifier */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FName ModifierID;
// 	
// 	UPROPERTY(EditAnywhere)
// 	ETekuaniStatsModifier ModifierType;
//
// 	/** Duration in seconds */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	float Duration = 0.f;
//
// 	/** Remaining time */
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	float TimeRemaining = 0.f;
// 	
// 	UPROPERTY(EditAnywhere)
// 	float TickInterval = 1.f;
// 	
// 	UPROPERTY()
// 	float TickTimer = 0.f;
//
// 	/** Flat modifiers */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FTekuaniCharacterStats FlatBonus;
//
// 	/** Percentage modifiers (0.2 = +20%) */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FTekuaniCharacterStats PercentBonus;
//
// 	/** Stack system */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	int32 MaxStacks = 1;
//
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	int32 CurrentStacks = 1;
// 	
// 	UPROPERTY(EditAnywhere)
// 	bool bStun = false;
//
// 	UPROPERTY(EditAnywhere)
// 	bool bSlow = false;
// };
