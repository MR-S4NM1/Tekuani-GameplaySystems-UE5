// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UTekuaniAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	check(InASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
	
	if (!InASCToGive) return;
	
	FGameplayEffectContextHandle ContextHandle = InASCToGive->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	for (const TSubclassOf<UGameplayEffect>& EffectClass : StartupGameplayEffects)
	{
		if (!EffectClass) continue;
		
		FGameplayEffectSpecHandle SpecHandle = InASCToGive->MakeOutgoingSpec(EffectClass, ApplyLevel, ContextHandle);
		
		if (SpecHandle.IsValid())
			InASCToGive->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UTekuaniGameplayAbility>>& InAbilitiesToGive,
	UTekuaniAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;
	
	for (const TSubclassOf<UTekuaniGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
