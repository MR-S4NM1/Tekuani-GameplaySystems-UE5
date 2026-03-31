// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "TekuaniInputComponent.generated.h"

/**
 * @class UTekuaniInputComponent
 * @brief Custom input component responsible for binding native and ability-related input actions.
 *
 * Extends UEnhancedInputComponent to integrate Tekuani's input system with a data-driven approach
 * using UDataAsset_InputConfig and Gameplay Tags.
 *
 * Responsibilities:
 * - Bind native input actions (movement, interaction, etc.) using gameplay tags.
 * - Bind ability input actions dynamically from a Data Asset configuration.
 * - Decouple input definitions from code through data-driven design.
 *
 * Architectural Role:
 * - Acts as the bridge between the Enhanced Input system and gameplay systems.
 * - Enables scalable input mapping without hardcoding InputActions in classes.
 *
 * Design Intent:
 * - Allow designers to configure inputs via DataAssets instead of modifying C++.
 * - Support Gameplay Ability System (GAS)-style input triggering using Gameplay Tags.
 * - Ensure flexibility for remapping and future extensibility (console/PC support).
 *
 * Notes:
 * - All input bindings rely on a valid UDataAsset_InputConfig.
 * - Ability bindings iterate over a predefined array of input configurations.
 */
UCLASS()
class MRSANMI_TEKUANI_API UTekuaniInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Binds a native input action using a Gameplay Tag.
	 *
	 * Retrieves an InputAction from the provided InputConfig using the given tag
	 * and binds it to the specified callback.
	 *
	 * @param InInputConfig Data asset containing input mappings.
	 * @param InInputTag Gameplay tag used to identify the input action.
	 * @param TriggerEvent Input trigger type (Started, Triggered, Completed, etc.).
	 * @param ContextObject Object that owns the callback function.
	 * @param Func Function to be executed when the input is triggered.
	 *
	 * This method is typically used for:
	 * - Movement
	 * - Camera
	 * - Interaction
	 */
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent,
		UserObject* ContextObject,
		CallbackFunc Func);
	
	/**
	 * @brief Binds all ability-related input actions defined in the InputConfig.
	 *
	 * Iterates through the AbilityInputActions array and binds each InputAction
	 * to both "Pressed" and "Released" callbacks using Gameplay Tags.
	 *
	 * @param InInputConfig Data asset containing ability input mappings.
	 * @param InInputConfig Data asset containing ability input mappings.
	 * @param ContextObject Object that owns the callback functions.
	 * @param InputPressedFunc Function executed when input is pressed (Started).
	 * @param InputReleasedFunc Function executed when input is released (Completed).
	 *
	 * Design Considerations:
	 * - Uses Gameplay Tags to identify abilities instead of hardcoded logic.
	 * - Enables seamless integration with GAS input handling.
	 * - Supports multiple abilities without modifying code.
	 *
	 * Example Use Case:
	 * - Press -> Activate ability (e.g., start aiming, charge attack)
	 * - Release -> Confirm or cancel ability (e.g., shoot, release charge)
	 */
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		UserObject* ContextObject,
		CallbackFunc InputPressedFunc,
		CallbackFunc InputReleasedFunc
		);
};

template <class UserObject, typename CallbackFunc>
void UTekuaniInputComponent::BindNativeInputAction(
	const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent,
	UserObject* ContextObject,
	CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can't proceed with binding!"));
	
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UTekuaniInputComponent::BindAbilityInputAction(
	const UDataAsset_InputConfig* InInputConfig,
	UserObject* ContextObject, 
	CallbackFunc InputPressedFunc, 
	CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can't proceed with binding!"));
	
	for (const FTekuaniInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;
		
		BindAction(AbilityInputActionConfig.InputAction,
			ETriggerEvent::Started,
			ContextObject, 
			InputPressedFunc, 
			AbilityInputActionConfig.InputTag
			);
		
		BindAction(AbilityInputActionConfig.InputAction,
			ETriggerEvent::Completed,
			ContextObject, 
			InputReleasedFunc, 
			AbilityInputActionConfig.InputTag
			);
	}
}
