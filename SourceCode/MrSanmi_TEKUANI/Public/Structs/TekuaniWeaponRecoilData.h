// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TekuaniWeaponRecoilData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponRecoilData
{
	GENERATED_BODY()
	
	/** Base vertical recoil applied per shot */
	UPROPERTY(EditAnywhere, Category = "Recoil", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
	float RecoilPitch = 2.0f;

	/** Max horizontal recoil variation */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilYawRange = 0.5f;

	/** How fast recoil returns to center */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilReturnSpeed = 6.0f ;

	/** How smooth the recoil interpolation feels */
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilDamping = 12.0f;

	/** Progression factor (0 = worst, 1 = perfect aim) */
	UPROPERTY(EditAnywhere, Category = "Recoil", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RecoilControl = 0.0f;
};