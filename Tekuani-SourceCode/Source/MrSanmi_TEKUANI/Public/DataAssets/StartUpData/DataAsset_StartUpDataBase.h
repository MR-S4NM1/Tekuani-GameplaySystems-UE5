// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UTekuaniAbilitySystemComponent;
class UTekuaniGameplayAbility;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(
		UTekuaniAbilitySystemComponent* InASCToGive,
		int32 ApplyLevel = 1
		);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UTekuaniGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UTekuaniGameplayAbility>> ReactiveAbilities;
	
	void GrantAbilities(
		const TArray<TSubclassOf<UTekuaniGameplayAbility>>& InAbilitiesToGive,
		UTekuaniAbilitySystemComponent* InASCToGive,
		int32 ApplyLevel = 1
		);
};
