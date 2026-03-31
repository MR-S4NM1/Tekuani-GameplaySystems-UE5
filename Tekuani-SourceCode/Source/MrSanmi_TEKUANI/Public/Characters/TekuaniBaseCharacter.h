//Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "TekuaniBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UTekuaniAttributeSet;
class UTekuaniAbilitySystemComponent;
/**
 * @class ATekuaniBaseCharacter
 * @brief Base class for all playable and non-playable characters in Tekuani.
 *
 * Inherits from APaperZDCharacter to integrate PaperZD animation support.
 *
 * Design Intent:
 * - Provide a lightweight foundation for all characters.
 * - Centralize shared character configuration.
 * - Serve as an extensible base for gameplay, AI, or player-controlled characters.
 *
 * Notes:
 * - Tick is disabled by default to optimize performance.
 * - Derived classes enable tick only when necessary.
 */
UCLASS()
class MRSANMI_TEKUANI_API ATekuaniBaseCharacter : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Default constructor.
	 *
	 * Initializes base configuration common to all characters.
	 */
	ATekuaniBaseCharacter();
	
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UTekuaniAbilitySystemComponent* TekuaniAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UTekuaniAttributeSet* TekuaniAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponSocket")
	USceneComponent* WeaponSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	
public:
	FORCEINLINE UTekuaniAbilitySystemComponent* GetTekuaniAbilitySystemComponent() const { return TekuaniAbilitySystemComponent; }
	
	FORCEINLINE UTekuaniAttributeSet* GetTekuaniAttributeSet() const { return TekuaniAttributeSet; }
};
