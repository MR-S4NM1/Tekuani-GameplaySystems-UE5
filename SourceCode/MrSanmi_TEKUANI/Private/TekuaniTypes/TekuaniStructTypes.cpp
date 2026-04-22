// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "TekuaniTypes/TekuaniStructTypes.h"
#include "AbilitySystem/Abilities/TekuaniGameplayAbility.h"

bool FTekuaniMarcelaAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
