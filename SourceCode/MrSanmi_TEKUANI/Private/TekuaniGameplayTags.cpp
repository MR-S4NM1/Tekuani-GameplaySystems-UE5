// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "TekuaniGameplayTags.h"

namespace TekuaniGameplayTags
{
	/** =========================
	 *  Input Gameplay Tags
	 *  ========================= */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Fire, "InputTag.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Parry, "InputTag.Parry");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipRevolver, "InputTag.Equip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipRevolver, "InputTag.Unequip.Revolver");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RightStickSpecialAction, "InputTag.RightStickSpecialAction");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Aiming, "Player.State.Aiming");
	
	/** =========================
	 *  Player Tags
	 *  ========================= */
	/** Player States */
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Health_Full, "Player.State.Health.Full");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Dodging, "Player.State.Dodging");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Invulnerable, "Player.State.Invulnerable");	
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Parrying, "Player.State.Parrying");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_ParryPerfect, "Player.State.ParryPerfect");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Staggered, "Player.State.Staggered");
	
	/** Player Weapon Abilities */
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Fire, "Player.Ability.Fire");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Revolver, "Player.Ability.Equip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Revolver, "Player.Ability.Unequip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Revolver_Cooldown, "Player.Ability.Weapon.Revolver.Cooldown");
	
	/** Player Abilities */
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge, "Player.Ability.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Parry, "Player.Ability.Parry");
	
	/** Player Weapons */
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Revolver, "Player.Weapon.Revolver");
	
	/** Player Ability Events */
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Parry_Success, "Player.Event.Parry.Success");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Stagger, "Player.Event.Stagger");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Revolver, "Player.Event.Equip.Revolver");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Revolver, "Player.Event.Unequip.Revolver");
}