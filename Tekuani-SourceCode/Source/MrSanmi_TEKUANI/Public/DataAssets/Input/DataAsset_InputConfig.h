// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * @struct FTekuaniInputActionConfig
 * @brief Defines a mapping between a Gameplay Tag and a native Input Action.
 *
 * This struct is used inside UDataAsset_InputConfig to create
 * a data-driven input system based on Gameplay Tags.
 *
 * Design Intent:
 * - Decouple input logic from hardcoded references.
 * - Allow scalable and modular input binding.
 * - Enable integration with Gameplay Ability System via tags.
 *
 * Architectural Role:
 * - Acts as the bridge between Enhanced Input and gameplay systems.
 */
USTRUCT(BlueprintType)
struct FTekuaniInputActionConfig
{
	GENERATED_BODY()
	
public:
	/** Gameplay tag that identifies this input action logically. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	/** Native Enhanced Input action associated with the tag. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

/**
 * @class UDataAsset_InputConfig
 * @brief Data-driven configuration asset for input bindings in Tekuani.
 *
 * Stores the default Input Mapping Context and the list of
 * native input actions mapped to Gameplay Tags.
 *
 * Architectural Role:
 * - Centralizes input configuration.
 * - Enables tag-based lookup for input-to-ability binding.
 * - Supports scalable input expansion without modifying C++ logic.
 *
 * Design Intent:
 * - Maintain separation between input assets and gameplay code.
 * - Allow designers to modify bindings safely via Data Assets.
 * - Integrate cleanly with GAS activation through tags.
 *
 * Notes:
 * - Designed for use with Enhanced Input.
 * - Works alongside Input Mapping Context initialization at runtime.
 */
UCLASS()
class MRSANMI_TEKUANI_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/** Default mapping context applied at gameplay initialization. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;
	
	/**
	 * Array of native input actions mapped to gameplay tags.
	 *
	 * TitleProperty ensures better readability inside the editor.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FTekuaniInputActionConfig> NativeInputActions;
	
	/**
	 * @brief Finds a native input action by its associated gameplay tag.
	 *
	 * @param InInputTag Gameplay tag used to identify the input.
	 * @return Pointer to the matching UInputAction, or nullptr if not found.
	 *
	 * This lookup enables tag-driven input handling
	 * without hardcoded references in gameplay systems.
	 */
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FTekuaniInputActionConfig> AbilityInputActions;
};
