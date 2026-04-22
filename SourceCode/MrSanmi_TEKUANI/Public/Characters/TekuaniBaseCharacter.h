//Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "TekuaniBaseCharacter.generated.h"

class UTekuaniHealthComponent;
class UDA_TekuaniCharacterBaseData;
class UTekuaniStatsComponent;
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
	
	virtual void BeginPlay() override;
	
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.
	
protected:
	UFUNCTION()
	virtual void BindDelegates();
	
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
	
	UPROPERTY(EditDefaultsOnly, Category = "CharacterStats")
	UDA_TekuaniCharacterBaseData* TekuaniCharacterBaseData;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	UTekuaniHealthComponent* TekuaniHealthComponent;
	
public:
	FORCEINLINE UTekuaniAbilitySystemComponent* GetTekuaniAbilitySystemComponent() const { return TekuaniAbilitySystemComponent; }
	FORCEINLINE UTekuaniAttributeSet* GetTekuaniAttributeSet() const { return TekuaniAttributeSet; }
	FORCEINLINE UTekuaniHealthComponent* GetHealthComponent() const { return TekuaniHealthComponent; }
	
protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tekuani|Movement")
	bool IsCharacterFalling() const;
	
public:
#pragma region Events
	UFUNCTION(BlueprintNativeEvent)
	void HandleDOT(float Damage);
	
	UFUNCTION(BlueprintNativeEvent)
	void HandleHOT(float Damage);
#pragma endregion Events
};
