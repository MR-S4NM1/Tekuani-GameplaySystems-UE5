// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_TekuaniItemStatsData.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UDA_TekuaniItemStatsData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
	FName ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Stats")
	TSubclassOf<UGameplayEffect> ItemStatEffectClass;
};