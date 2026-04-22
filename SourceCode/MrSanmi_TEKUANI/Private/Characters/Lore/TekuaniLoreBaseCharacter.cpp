// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Characters/Lore/TekuaniLoreBaseCharacter.h"

ATekuaniLoreBaseCharacter::ATekuaniLoreBaseCharacter()
{
	/**
	 * Tick is disabled by default for performance optimization. 
	 * Since this base class does not implement per-frame logic, 
	 * ticking is unnecessary unless explicitly required by child classes.
	 * Derived classes can enable ticking if they introduce
	 * time-dependent behavior. 
	 */ 
	PrimaryActorTick.bCanEverTick = false; 
	PrimaryActorTick.bStartWithTickEnabled = false;
}
