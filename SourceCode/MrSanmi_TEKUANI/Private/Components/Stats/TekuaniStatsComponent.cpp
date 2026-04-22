// // Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved
//
// #include "Components/Stats/TekuaniStatsComponent.h"
//
// #include "TekuaniDebugHelper.h"
//
// // Sets default values for this component's properties
// UTekuaniStatsComponent::UTekuaniStatsComponent()
// {
// 	PrimaryComponentTick.bCanEverTick = false;
// }
//
// void UTekuaniStatsComponent::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// 	if (GetWorld())
// 		GetWorld()->GetTimerManager().SetTimer(
// 			BuffTimerHandle,
// 			this,
// 			&UTekuaniStatsComponent::UpdateBuffs,
// 			StatsModifierTickInterval,
// 			true);
// }
//
// void UTekuaniStatsComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
// {
// 	if (GetWorld())
// 		GetWorld()->GetTimerManager().ClearTimer(BuffTimerHandle);
// 	
// 	Super::EndPlay(EndPlayReason);
// }
//
// void UTekuaniStatsComponent::InitializeStats(const FTekuaniCharacterStats& InBaseStats)
// {
// 	BaseStats = InBaseStats;
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::RecalculateStats()
// {
// 	LevelScaledStats = BaseStats;
// 	
// 	// 1. Level scaling
// 	ApplyLevelScaling();
//
// 	// 2. Equipment
// 	ApplyEquipmentModifiers();
//
// 	// 3. Buffs / Debuffs
// 	ApplyTemporaryModifiers();
// 	
// 	// 4. Applying clamp
// 	LevelScaledStats.Haste = FMath::Clamp(LevelScaledStats.Haste, 0.f, 0.9f);
// 	LevelScaledStats.CritChance = FMath::Clamp(LevelScaledStats.CritChance, 0.f, 1.f);
// 	LevelScaledStats.MovementSpeed = FMath::Clamp(LevelScaledStats.MovementSpeed, 0.f, 2000.f);
//
// 	// 5. Final result
// 	FinalStats = LevelScaledStats;
// 	TekuaniDebug::Print(FString::Printf(TEXT("Attack: %f"), FinalStats.Attack));
// 	
// 	if (OnStatsUpdated.IsBound())
// 		OnStatsUpdated.Broadcast();
// }
//
// void UTekuaniStatsComponent::ApplyLevelScaling()
// {
// 	float AttackMultiplier = 1.0f;
// 	float DefenseMultiplier = 1.0f;
// 	float HealthMultiplier = 1.0f;
//
// 	if (AttackLevelCurve)
// 		AttackMultiplier = AttackLevelCurve->GetFloatValue(BaseStats.Level);
// 	if (DefenseLevelCurve)
// 		DefenseMultiplier = DefenseLevelCurve->GetFloatValue(BaseStats.Level);
// 	if (HealthLevelCurve)
// 		HealthMultiplier = HealthLevelCurve->GetFloatValue(BaseStats.Level);
// 	
// 	LevelScaledStats.MaxHealth = BaseStats.MaxHealth * HealthMultiplier;
// 	LevelScaledStats.Attack = BaseStats.Attack * AttackMultiplier;
// 	LevelScaledStats.Defense = BaseStats.Defense * DefenseMultiplier;
// }
//
// void UTekuaniStatsComponent::ApplyEquipmentModifiers()
// {
// 	for (const UDA_TekuaniItemStatsData* Item : EquippedItems)
// 	{
// 		if (!Item) continue;
// 		
// 		LevelScaledStats += Item->ItemStats;
// 	}
// }
//
// void UTekuaniStatsComponent::ApplyTemporaryModifiers()
// {
// 	for (const FActiveStatModifier& StatModifier : ActiveModifiers)
// 	{
// 		const int32 Stacks = StatModifier.CurrentStacks;
// 		
// 		// FLAT
// 		LevelScaledStats.Attack += StatModifier.FlatBonus.Attack;
// 		LevelScaledStats.Defense += StatModifier.FlatBonus.Defense;
// 		LevelScaledStats.MaxHealth += StatModifier.FlatBonus.MaxHealth;
// 		LevelScaledStats.MovementSpeed += StatModifier.FlatBonus.MovementSpeed;
// 		
// 		// PERCENT
// 		LevelScaledStats.Attack *= (1.f + StatModifier.PercentBonus.Attack * Stacks);
// 		LevelScaledStats.Defense *= (1.f + StatModifier.PercentBonus.Defense * Stacks);
// 		LevelScaledStats.MaxHealth *= (1.f + StatModifier.PercentBonus.MaxHealth * Stacks);
// 		LevelScaledStats.MovementSpeed *= (1.f + StatModifier.PercentBonus.MovementSpeed * Stacks);
// 	}
// }
//
// void UTekuaniStatsComponent::OnLevelUp(int32 NewLevel)
// {
// 	SetLevel(NewLevel);
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::SetLevel(int32 NewLevel)
// {
// 	BaseStats.Level = NewLevel;
// }
//
// void UTekuaniStatsComponent::OnEquipItem(UDA_TekuaniItemStatsData* ItemData)
// {
// 	EquippedItems.Add(ItemData);
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::OnUnequipItem(UDA_TekuaniItemStatsData* ItemData)
// {
// 	EquippedItems.Remove(ItemData);
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::OnStatEffectModifierApplied(const FActiveStatModifier& NewBuff)
// {
// 	ApplyStatsModifier(NewBuff);
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::ApplyStatsModifier(const FActiveStatModifier& NewBuff)
// {
// 	if (!GetWorld()->GetTimerManager().IsTimerActive(BuffTimerHandle))
// 	{
// 		GetWorld()->GetTimerManager().SetTimer(
// 			BuffTimerHandle,
// 			this,
// 			&UTekuaniStatsComponent::UpdateBuffs,
// 			StatsModifierTickInterval,
// 			true
// 		);
// 	}
// 	
// 	for (FActiveStatModifier& Buff : ActiveModifiers)
// 	{
// 		if (Buff.ModifierID == NewBuff.ModifierID)
// 		{
// 			// Stack or refresh
// 			if (Buff.CurrentStacks < Buff.MaxStacks)
// 				Buff.CurrentStacks++;
// 			
// 			Buff.TimeRemaining = NewBuff.Duration;
// 			RecalculateStats();
// 			return;
// 		}
// 	}
// 	
// 	// New buff
// 	FActiveStatModifier Buff = NewBuff;
// 	Buff.TimeRemaining = Buff.Duration;
// 	ActiveModifiers.Add(Buff);
// 	
// 	RecalculateStats();
// }
//
// void UTekuaniStatsComponent::UpdateBuffs()
// {
// 	bool bChanged = false;
//
// 	for (int32 i = ActiveModifiers.Num() - 1; i >= 0; --i)
// 	{
// 		FActiveStatModifier& Buff = ActiveModifiers[i];
// 		Buff.TimeRemaining -= StatsModifierTickInterval;
//
// 		// Over Time
// 		if (Buff.ModifierType == ETekuaniStatsModifier::OverTime)
// 			ApplyOverTimeEffect(Buff);
//
// 		if (Buff.TimeRemaining <= 0.f)
// 		{
// 			ActiveModifiers.RemoveAt(i);
// 			bChanged = true;
// 		}
// 	}
//
// 	if (bChanged)
// 		RecalculateStats();
// 	
// 	if (ActiveModifiers.IsEmpty())
// 		GetWorld()->GetTimerManager().ClearTimer(BuffTimerHandle);
// }
//
// void UTekuaniStatsComponent::ApplyOverTimeEffect(const FActiveStatModifier& Buff)
// {
// 	/**
// 	 * Applies periodic effects such as damage over time (DOT) or healing over time (HOT).
// 	 *
// 	 * Design:
// 	 * - Positive Attack -> Damage (DOT)
// 	 * - Negative Attack -> Heal (HOT)
// 	 * - Scales with stacks
// 	 */
// 	const float ScaledValue = Buff.FlatBonus.Attack * Buff.CurrentStacks;
//
// 	if (ScaledValue > 0.f) // Damage Over Time
// 	{
// 		if (OnDamageOverTime.IsBound())
// 			OnDamageOverTime.Broadcast(ScaledValue);
// 	}
// 	else if (ScaledValue < 0.f) // Heal Over Time
// 	{
// 		if (OnHealOverTime.IsBound())
// 			OnHealOverTime.Broadcast(ScaledValue);
// 	}
// }
//
// void UTekuaniStatsComponent::ApplyDamage(float Damage)
// {
// 	// TODO:
// 	// Connect this function with the GAS or HealthComponent
// 	// OwnerCharacter->GetHealthComponent()->ApplyDamage(Damage);
// }
//
// void UTekuaniStatsComponent::ApplyHeal(float HealAmount)
// {
// 	// TODO:
// 	// Connect this function with the GAS or HealthComponent
// 	// OwnerCharacter->GetHealthComponent()->Heal(HealAmount);
// }
//
// float UTekuaniStatsComponent::GetAttack() const
// {
// 	return FinalStats.Attack;
// }
//
// float UTekuaniStatsComponent::GetDefense() const
// {
// 	return FinalStats.Defense;
// }
//
// float UTekuaniStatsComponent::GetMaxHealth() const
// {
// 	return FinalStats.MaxHealth;
// }
//
// int32 UTekuaniStatsComponent::GetLevel() const
// {
// 	return BaseStats.Level;
// }
