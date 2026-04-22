// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "GameplayTagContainer.h"
#include "TekuaniStructTypes.generated.h"

enum EMarcela_CorporalPosture : uint8;
class UInputMappingContext;
class UTekuaniGameplayAbility;

USTRUCT(BlueprintType)
struct FTekuaniMarcelaAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UTekuaniGameplayAbility> AbilityToGrant;
	
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FTekuaniMarcelaWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FTekuaniMarcelaAbilitySet> DefaultWeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TEnumAsByte<EMarcela_CorporalPosture> AbilityPostureState;
};
