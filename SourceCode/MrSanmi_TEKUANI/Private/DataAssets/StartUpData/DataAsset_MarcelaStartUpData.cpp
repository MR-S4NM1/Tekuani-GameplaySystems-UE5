// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_MarcelaStartUpData.h"

#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"

void UDataAsset_MarcelaStartUpData::GiveToAbilitySystemComponent(UTekuaniAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	for (const FTekuaniMarcelaAbilitySet& AbilitySet : MarcelaStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
