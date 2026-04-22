// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniWeaponSwayData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSwayData
{
	GENERATED_BODY()
	
	/** ===== CONFIG ===== */
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwayAmplitude { 1.5f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwaySpeed { 2.f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwayRecoverySpeed { 5.f };
};
