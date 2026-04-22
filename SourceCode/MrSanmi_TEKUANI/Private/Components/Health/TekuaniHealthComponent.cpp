// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Components/Health/TekuaniHealthComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TekuaniAttributeSet.h"

UTekuaniHealthComponent::UTekuaniHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	CurrentHealth = 0.f;
	MaxHealth = 0.f;
	bIsDead = false;
}

void UTekuaniHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ASComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();

	UpdateMaxHealthFromStats();
	CurrentHealth = MaxHealth;
}

void UTekuaniHealthComponent::ApplyDamage(float Damage)
{
	if (bIsDead || Damage <= 0.f) return;

	float Defense = 0.f;

	if (ASComponent)
		Defense = ASComponent->GetNumericAttribute(UTekuaniAttributeSet::GetDefenseAttribute());

	float FinalDamage = Damage * (100.f / (100.f + Defense));

	CurrentHealth -= FinalDamage;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if (OnHealthChanged.IsBound())
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.f)
		HandleDeath();
}

void UTekuaniHealthComponent::ApplyHeal(float HealAmount)
{
	if (bIsDead || HealAmount <= 0.f) return;
	
	CurrentHealth += HealAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
	
	if (OnHealthChanged.IsBound())
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UTekuaniHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);

	if (OnHealthChanged.IsBound())
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.f && !bIsDead)
		HandleDeath();
}

void UTekuaniHealthComponent::HandleDeath()
{
	if (bIsDead) return;

	bIsDead = true;

	if (OnDeath.IsBound())
		OnDeath.Broadcast();
}

void UTekuaniHealthComponent::UpdateMaxHealthFromStats()
{
	if (!ASComponent) return;

	float OldMaxHealth = MaxHealth;
	MaxHealth = ASComponent->GetNumericAttribute(UTekuaniAttributeSet::GetMaxHealthAttribute());
	
	if (OldMaxHealth > 0.f)
	{
		float HealthPercent = CurrentHealth / OldMaxHealth;
		CurrentHealth = MaxHealth * HealthPercent;
	}

	if (OnHealthChanged.IsBound())
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

