// // Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "Components/ActorComponent.h"
// #include "DataAssets/Stats/DA_TekuaniItemStatsData.h"
// #include "Structs/TekuaniStatusEffect.h"
// #include "TekuaniStatsComponent.generated.h"
//
// class UDataAsset;
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageOverTime, float, Damage);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealOverTime, float, Damage);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsUpdated);
//
// /**
//  * @class UTekuaniStatsComponent
//  * @brief Handles all stat-related calculations and access for a character.
//  *
//  * Responsibilities:
//  * - Store base stats from DataAssets
//  * - Calculate final stats (level scaling, modifiers, etc.)
//  * - Provide access to computed values for other systems
//  *
//  * Design Intent:
//  * - Centralize all stat logic in a single modular component
//  * - Keep Character classes lightweight
//  * - Support data-driven balancing
//  *
//  * Notes:
//  * - Does NOT handle XP or leveling logic (handled by ProgressionSubsystem)
//  */
// UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
// class MRSANMI_TEKUANI_API UTekuaniStatsComponent : public UActorComponent
// {
// 	GENERATED_BODY()
//
// public:	
// 	// Sets default values for this component's properties
// 	UTekuaniStatsComponent();
// 	
// 	virtual void BeginPlay() override;
// 	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
//
// 	/** Initializes stats from a DataAsset */
// 	void InitializeStats(const FTekuaniCharacterStats& InBaseStats);
// 	
// 	/** Recalculates final stats (after modifiers) */
// 	void RecalculateStats();
// 	
// 	void ApplyLevelScaling();
// 	void ApplyEquipmentModifiers();
// 	void ApplyTemporaryModifiers();
// 	
// 	void OnLevelUp(int32 NewLevel);
// 	void SetLevel(int32 NewLevel);
// 	
// 	void OnEquipItem(UDA_TekuaniItemStatsData* ItemData);
// 	void OnUnequipItem(UDA_TekuaniItemStatsData* ItemData);
// 	
// 	void OnStatEffectModifierApplied(const FActiveStatModifier& NewBuff);
// 	void ApplyStatsModifier(const FActiveStatModifier& NewBuff);
// 	void UpdateBuffs();
// 	void ApplyOverTimeEffect(const FActiveStatModifier& Buff);
// 	
// private:
// 	void ApplyDamage(float Damage);
// 	void ApplyHeal(float HealAmount);
// 	
// public:
// 	/** Getters */
// 	float GetAttack() const;
// 	float GetDefense() const;
// 	float GetMaxHealth() const;
// 	int32 GetLevel() const;
// 	
// 	
// private:
// 	/** Base stats from DataAsset */
// 	FTekuaniCharacterStats BaseStats;
// 	
// 	/** Level Scaled stats */
// 	FTekuaniCharacterStats LevelScaledStats;
// 	
// 	/** Final computed stats */
// 	FTekuaniCharacterStats FinalStats;
// 	
// 	UPROPERTY()
// 	TArray<FActiveStatModifier> ActiveModifiers;
// 	
// 	UPROPERTY()
// 	TArray<TObjectPtr<UDA_TekuaniItemStatsData>> EquippedItems;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	UCurveFloat* AttackLevelCurve;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	UCurveFloat* DefenseLevelCurve;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	UCurveFloat* HealthLevelCurve;
// 	
// 	/** Buff timer */
// 	FTimerHandle BuffTimerHandle;
// 	
// 	/** Update interval */
// 	float StatsModifierTickInterval = 0.1f;
// 	
// public:
// 	UPROPERTY(BlueprintAssignable)
// 	FOnDamageOverTime OnDamageOverTime;
// 	
// 	UPROPERTY(BlueprintAssignable)
// 	FOnHealOverTime OnHealOverTime;
// 	
// 	UPROPERTY(BlueprintAssignable)
// 	FOnStatsUpdated OnStatsUpdated;
// };
