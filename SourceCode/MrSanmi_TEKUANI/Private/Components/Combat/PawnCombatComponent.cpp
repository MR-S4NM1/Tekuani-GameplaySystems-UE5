// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "TekuaniDebugHelper.h"
#include "Items/Weapons/TekuaniWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
	ATekuaniWeaponBase* InWeaponToRegister, 
	bool bRegisterAsEquippedWeapon)
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister))
		TekuaniDebug::Print("Weapon already registered!");
	
	checkf(!CharacterCarriedWeaponMap.Contains(
		InWeaponTagToRegister), 
		TEXT("A tag named %s has already been added as carried weapon"), 
		*InWeaponTagToRegister.ToString());
	
	if (!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister))
		CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	
	if (bRegisterAsEquippedWeapon)
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	
	const FString WeaponString = FString::Printf(
		TEXT("A weapon named: %s has been registered using the tag %s"),
		*InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	
	TekuaniDebug::Print(WeaponString);
}

ATekuaniWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (ATekuaniWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
			return *FoundWeapon;
	}
	return nullptr;
}

ATekuaniWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
	
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
