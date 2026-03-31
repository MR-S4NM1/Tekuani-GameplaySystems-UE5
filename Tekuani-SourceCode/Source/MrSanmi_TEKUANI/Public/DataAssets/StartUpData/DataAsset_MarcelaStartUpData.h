// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "TekuaniTypes/TekuaniStructTypes.h" 
#include "DataAsset_MarcelaStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UDataAsset_MarcelaStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(
		UTekuaniAbilitySystemComponent* InASCToGive,
		int32 ApplyLevel = 1
		) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FTekuaniMarcelaAbilitySet> MarcelaStartUpAbilitySets;
};
