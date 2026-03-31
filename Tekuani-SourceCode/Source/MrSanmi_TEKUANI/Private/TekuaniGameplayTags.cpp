// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "TekuaniGameplayTags.h"

namespace TekuaniGameplayTags
{
	/** =========================
	 *  Input Gameplay Tags
	 *  ========================= */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipRevolver, "InputTag.EquipRevolver");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipRevolver, "InputTag.UnequipRevolver");
	
	/** =========================
	 *  Player Tags
	 *  ========================= */
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Revolver, "Player.Ability.Equip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Revolver, "Player.Ability.Unequip.Revolver");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Revolver, "Player.Weapon.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Revolver, "Player.Event.Equip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Revolver, "Player.Event.Unequip.Revolver");
}