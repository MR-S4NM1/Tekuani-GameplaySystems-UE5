// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "AbilitySystem/Abilities/TekuaniMarcelaGameplayAbility.h"
#include "Characters/TekuaniMarcelaCharacter.h"
#include "Controllers/TekuaniMarcelaController.h"

ATekuaniMarcelaCharacter* UTekuaniMarcelaGameplayAbility::GetMarcelaCharacterFromActorInfo()
{
	if (!CachedTekuaniMarcelaCharacter.IsValid())
		CachedTekuaniMarcelaCharacter = Cast<ATekuaniMarcelaCharacter>(CurrentActorInfo->AvatarActor);
	
	return CachedTekuaniMarcelaCharacter.IsValid() ? CachedTekuaniMarcelaCharacter.Get() : nullptr;
}

ATekuaniMarcelaController* UTekuaniMarcelaGameplayAbility::GetMarcelaControllerFromActorInfo()
{
	if (!CachedTekuaniMarcelaController.IsValid())
		CachedTekuaniMarcelaController = Cast<ATekuaniMarcelaController>(CurrentActorInfo->PlayerController);
	
	return CachedTekuaniMarcelaController.IsValid() ? CachedTekuaniMarcelaController.Get() : nullptr;
}

UMarcelaCombatComponent* UTekuaniMarcelaGameplayAbility::GetMarcelaCombatComponentFromActorInfo()
{
	return GetMarcelaCharacterFromActorInfo()->GetMarcelaCombatComponent();
}