// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	/**
	 * Performs a linear search through the configured input mappings.
	 *
	 * Given the expected small dataset size (limited input actions),
	 * O(n) lookup is acceptable and keeps implementation simple.
	 *
	 * If the project scales significantly,
	 * this could be replaced with a TMap for faster access.
	 */
	for (const FTekuaniInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	
	// No matching input action found.
	return nullptr;
}
