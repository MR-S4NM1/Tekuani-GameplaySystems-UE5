// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "NativeGameplayTags.h"

/**
 * @namespace TekuaniGameplayTags
 * @brief Centralized declaration of native Gameplay Tags used across Tekuani.
 *
 * Design Goals:
 * - Provide compile-time validated gameplay tags.
 * - Avoid hardcoded string usage throughout gameplay systems.
 * - Enable safe integration with GAS and Enhanced Input.
 *
 * Usage:
 * - Tags declared here must be defined in the corresponding .cpp file.
 * - Always access tags via TekuaniGameplayTags namespace.
 *
 * Example:
 *   TekuaniGameplayTags::InputTag_Move
 */
namespace TekuaniGameplayTags
{
	/** =========================
	 *  Input Gameplay Tags
	 *  ========================= */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipRevolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipRevolver);
	
	/** =========================
	 *  Player Tags
	 *  ========================= */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Revolver);
		
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Revolver);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Revolver);
}
