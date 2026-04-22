// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "AbilitySystem/TekuaniAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "TekuaniGameplayTags.h"

UTekuaniAttributeSet::UTekuaniAttributeSet()
{
}

void UTekuaniAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetCurrentHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	else if (Attribute == GetMovementSpeedAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, 2000.f);
	else if (Attribute == GetHasteAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, 0.9f);
}

void UTekuaniAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	if (Attribute == GetCurrentHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
}

void UTekuaniAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentHealthAttribute())
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		if (!ASC) return;
		
		FGameplayTag FullHealthTag = FGameplayTag::RequestGameplayTag(FName("Player.State.Health.Full"));
		
		if (NewValue >= GetMaxHealth() - KINDA_SMALL_NUMBER)
			ASC->AddLooseGameplayTag(FullHealthTag);
		else
			ASC->RemoveLooseGameplayTag(FullHealthTag);
		
		FString HealthMessage = FString::Printf(TEXT("Vida de Marcela: %f / %f"), NewValue, GetMaxHealth());
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, HealthMessage);
	}
}

void UTekuaniAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		float LocalDamage = GetDamage();
		SetDamage(0.0f);

		if (LocalDamage > 0.0f)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			if (!ASC) return;

			// ===== TAG CHECK =====
			if (ASC->HasMatchingGameplayTag(TekuaniGameplayTags::Player_State_Invulnerable))
				return;

			if (ASC->HasMatchingGameplayTag(TekuaniGameplayTags::Player_State_ParryPerfect))
			{
				ASC->HandleGameplayEvent(
					TekuaniGameplayTags::Player_Event_Parry_Success,
					nullptr
				);
				return;
			}

			if (ASC->HasMatchingGameplayTag(TekuaniGameplayTags::Player_State_Parrying))
				LocalDamage *= 0.2f;
			else if (ASC->HasMatchingGameplayTag(TekuaniGameplayTags::Player_State_Dodging))
				LocalDamage *= 0.5f;

			// ===== DEFENSE =====
			float CurrentDefense = GetDefense();
			float FinalDamage = LocalDamage * (100.f / (100.f + CurrentDefense));

			float NewHealth = GetCurrentHealth() - FinalDamage;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetStaggerDamageAttribute())
	{
		float LocalStaggerDamage = GetStaggerDamage();
		SetStaggerDamage(0.0f);
		
		if (LocalStaggerDamage > 0.0f)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			if (!ASC) return;
			
			// Reduction by resistance
			float Resistance = GetStaggerResistance();
			float FinalStagger = LocalStaggerDamage * (100.f / (100.f + Resistance));
			float NewStagger = GetStagger() + FinalStagger;
			
			if (NewStagger >= GetMaxStagger())
			{
				// Stagger is triggered
				ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Player.State.Staggered"));
				
				NewStagger = 0.f; // Reset meter
				
				// Animation Event
				ASC->HandleGameplayEvent(
					FGameplayTag::RequestGameplayTag("Player.Event.Stagger"),
					nullptr
					);
			}
			
			SetStagger(NewStagger);
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		if (!ASC) return;
		
		FGameplayTag FullHealthTag = FGameplayTag::RequestGameplayTag(FName("Player.State.Health.Full"));
		
		if (GetCurrentHealth() >= GetMaxHealth() - KINDA_SMALL_NUMBER)
			ASC->AddLooseGameplayTag(FullHealthTag);
		else
			ASC->RemoveLooseGameplayTag(FullHealthTag);
	}
}
