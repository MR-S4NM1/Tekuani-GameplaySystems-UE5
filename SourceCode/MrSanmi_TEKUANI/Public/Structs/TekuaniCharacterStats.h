// // Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "Structs/TekuaniItemStats.h"
// #include "TekuaniCharacterStats.generated.h"
//
// USTRUCT(BlueprintType)
// struct FTekuaniCharacterStats
// {
// 	GENERATED_BODY()
// 	
// 	/** Level scaling */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
// 	int32 Level = 1;
//     
// 	/** Maximum health of the character */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
// 	float MaxHealth = 100.f;
//     
// 	/** Base attack power */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
// 	float Attack = 10.f;
//     
// 	/** Defense used for damage mitigation */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
// 	float Defense = 10.f;
//     
// 	/** Movement speed */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
// 	float MovementSpeed = 600.f;
//     
// 	/** Cooldown reduction (0–1 range) */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
// 	float Haste = 0.f;
// 	
// 	/** Damage multiplier produced by a critical hit */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	float CritDamage = 3.f;
// 	
// 	/** Chance of producing a critical hit / damage */
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	float CritChance = 0.01f;
// 	
// 	//TODO:
// 	// FTekuaniCharacterStats& operator+=(const FTekuaniItemStats& Other)
// 	// {
// 	// 	Attack += Other.AttackBonus;
// 	// 	Defense += Other.DefenseBonus;
// 	// 	MaxHealth += Other.MaxHealthBonus;
// 	// 	Haste += Other.HasteBonus;
// 	// 	CritChance += Other.CriticalChanceBonus;
// 	// 	CritDamage *= (1.f + Other.CriticalDamageBonus);
// 	// 	MovementSpeed += Other.MovementSpeedBonus;
// 	//
// 	// 	return *this;
// 	// }
// 	
// 	FTekuaniCharacterStats& operator+=(const FTekuaniCharacterStats& Other)
// 	{
// 		Attack += Other.Attack;
// 		Defense += Other.Defense;
// 		MaxHealth += Other.MaxHealth;
// 		Haste += Other.Haste;
// 		CritChance += Other.CritChance;
// 		CritDamage += Other.CritDamage;
// 		MovementSpeed += Other.MovementSpeed;
//
// 		return *this;
// 	}
// };
