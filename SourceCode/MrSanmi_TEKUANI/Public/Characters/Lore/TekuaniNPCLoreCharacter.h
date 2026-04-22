// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/Lore/TekuaniLoreBaseCharacter.h"
#include "Interfaces/Interaction/TekuaniInteractable.h"
#include "TekuaniNPCLoreCharacter.generated.h"

class USphereComponent;
/**
 * @class ATekuaniNPCLoreCharacter
 * @brief Base class for all NPCs present in lore / town environments.
 *
 * Responsibilities:
 * - Provide interaction capability with the player.
 * - Serve as a foundation for dialogue-driven NPCs.
 * - Remain lightweight (no combat systems attached).
 */
UCLASS(Blueprintable)
class MRSANMI_TEKUANI_API ATekuaniNPCLoreCharacter : public ATekuaniLoreBaseCharacter, public ITekuaniInteractable
{
	GENERATED_BODY()
	
public:
	/** @brief Default constructor. */
	ATekuaniNPCLoreCharacter();
	
	/** Interaction entry point triggered by the player */
	virtual void Interact_Implementation(AActor* Interactor) override;
	
private:
	/** Simple sphere collision for interaction system */
	UPROPERTY(EditDefaultsOnly, Category = "LoreInteraction")
	USphereComponent* InteractionSphere;
};
