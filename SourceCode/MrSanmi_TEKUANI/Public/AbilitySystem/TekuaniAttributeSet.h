// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TekuaniAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UTekuaniAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTekuaniAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Level")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Level)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, CurrentHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Defense)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Speed")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, MovementSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Haste")
	FGameplayAttributeData Haste;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Haste)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|CritDamage")
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, CritDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|CritChance")
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, CritChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Meta")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Damage)
	
#pragma region Stagger
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stagger")
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, Stagger)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stagger")
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, MaxStagger)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stagger")
	FGameplayAttributeData StaggerResistance;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, StaggerResistance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stagger")
	FGameplayAttributeData StaggerDamage;
	ATTRIBUTE_ACCESSORS(UTekuaniAttributeSet, StaggerDamage)
	
#pragma endregion Stagger
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
