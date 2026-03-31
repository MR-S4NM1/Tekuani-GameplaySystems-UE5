// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TekuaniInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTekuaniInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for any object that can be interacted with by the player.
 */
class MRSANMI_TEKUANI_API ITekuaniInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Called when the player interacts with this actor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* Interactor);
};
