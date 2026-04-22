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
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Fire);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dodge);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Parry);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Revolver);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RightStickSpecialAction);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Aiming);
	
	/** =========================
	 *  Player Tags
	 *  ========================= */
	
	/** Player States */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Health_Full);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Dodging);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Invulnerable);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Parrying);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_ParryPerfect);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Staggered);

	/** Player Weapon Abilities */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Fire);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Weapon_Revolver_Cooldown);
	
	/** Player Abilities */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Dodge);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Parry);
	
	/** Player Weapons */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Revolver);
	
	/** Player Ability Events */
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Parry_Success);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Stagger);
	
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Revolver);
	MRSANMI_TEKUANI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Revolver);
}
