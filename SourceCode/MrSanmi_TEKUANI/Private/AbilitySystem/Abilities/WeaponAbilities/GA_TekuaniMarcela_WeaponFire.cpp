// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "AbilitySystem/Abilities/WeaponAbilities/GA_TekuaniMarcela_WeaponFire.h"
#include "AbilitySystemComponent.h"
#include "TekuaniDebugHelper.h"
#include "Components/Combat/MarcelaCombatComponent.h"
#include "Controllers/TekuaniMarcelaController.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "DataAssets/Weapons/DA_TekuaniWeaponDefinition.h"
#include "Items/Weapons/TekuaniMarcelaWeapon.h"

UGA_TekuaniMarcela_WeaponFire::UGA_TekuaniMarcela_WeaponFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_TekuaniMarcela_WeaponFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	// {
	// 	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	// 	return;
	// }
	//
	// UMarcelaCombatComponent* MarcelaCombatComponent = GetMarcelaCombatComponentFromActorInfo();
	// if (!MarcelaCombatComponent || !MarcelaCombatComponent->IsAiming())
	// {
	// 	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	// 	return;
	// }
	//
	// PerformHitscan();
	//
	// EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	
	UMarcelaCombatComponent* MarcelaCombatComponent = GetMarcelaCombatComponentFromActorInfo();
	if (!MarcelaCombatComponent || !MarcelaCombatComponent->IsAiming())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	UDA_TekuaniWeaponDefinition* CurrentWeaponData = MarcelaCombatComponent->GetCurrentWeaponDefinition();
	
	ATekuaniMarcelaWeapon* WeaponActor = MarcelaCombatComponent->GetMarcelaCarriedWeaponByTag(MarcelaCombatComponent->CurrentWeaponDefinition->BaseData->WeaponTag);
	
	if (!CurrentWeaponData || !CurrentWeaponData->FireModesData || CurrentWeaponData->FireModesData->AvailableFireModes.IsEmpty())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	int32 ActiveIndex = WeaponActor ? WeaponActor->GetCurrentFireModeIndex() : 0;
	
	if (!CurrentWeaponData->FireModesData->AvailableFireModes.IsValidIndex(ActiveIndex))
		ActiveIndex = 0;
	
	const FTekuaniWeaponFireModeData& ActiveModeData = CurrentWeaponData->FireModesData->AvailableFireModes[ActiveIndex];
	
	ETekuaniWeaponFireMode FireMode = ActiveModeData.FireMode;
	MaxBurstShots = ActiveModeData.BurstCount;
	
	BurstDelay = 60.f / FMath::Max(ActiveModeData.FireRate, 1.f);
	
	UAbilityTask_WaitInputRelease* InputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	InputReleaseTask->OnRelease.AddDynamic(this, &UGA_TekuaniMarcela_WeaponFire::OnInputReleased);
	InputReleaseTask->ReadyForActivation();
	
	switch (FireMode)
	{
		case ETekuaniWeaponFireMode::SemiAuto:
			if (CommitAbility(Handle, ActorInfo, ActivationInfo))
			{
				TekuaniDebug::Print(TEXT("TA"));
				PerformHitscan();
			}
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			break;
			
		case ETekuaniWeaponFireMode::FullAuto:
			// TODO: FIX THISSS
			FireFullAutoLoop();
			break;
			
		case ETekuaniWeaponFireMode::Burst:
			BurstShotsFired = 0;
			FireBurstLoop();
			break;
	}
}

void UGA_TekuaniMarcela_WeaponFire::PerformHitscan()
{
	ATekuaniMarcelaController* PC = GetMarcelaControllerFromActorInfo();
	UMarcelaCombatComponent* CombatComponent = GetMarcelaCombatComponentFromActorInfo();
	if (!PC || !CombatComponent) return;
	
	UDA_TekuaniWeaponDefinition* CurrentWeaponData = CombatComponent->GetCurrentWeaponDefinition();
	float TraceDistance = CurrentWeaponData->BaseData->BaseStats.Range;
	
	int32 ViewportSizeX, ViewportSizeY;
	PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
	const FVector2D ScreenCenter(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
	
	FVector WorldLocation;
	FVector WorldDirection;
	
	if (PC->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * TraceDistance);
		
		FHitResult HitResult;
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(GetAvatarActorFromActorInfo()->Owner);
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParameters);
		
		if (bHit && HitResult.GetActor())
		{
			UAbilitySystemComponent* TargetASC = HitResult.GetActor()->FindComponentByClass<UAbilitySystemComponent>();
			if (TargetASC)
			{
				TSubclassOf<UGameplayEffect> DamageEffectClass = CurrentWeaponData->BaseData->BaseStats.DamageEffect;
				if (DamageEffectClass)
				{
					FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
					EffectContext.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
					EffectContext.AddHitResult(HitResult);

					FGameplayEffectSpecHandle DamageSpec = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
						DamageEffectClass, 
						GetAbilityLevel(), 
						EffectContext
					);

					if (DamageSpec.IsValid())
						TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpec.Data.Get());
				}
				else
					TekuaniDebug::Print(TEXT("Fallo al aplicar GE: El arma no tiene un DamageEffect asignado en su definición."));
			}
		}
		
		CombatComponent->ApplyRecoil(CurrentWeaponData->RecoilData->RecoilData);
	}
}

void UGA_TekuaniMarcela_WeaponFire::OnInputReleased(float TimeHeld)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_TekuaniMarcela_WeaponFire::FireFullAutoLoop()
{
	
	// TODO: FIX THIS
	if (CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		PerformHitscan();
		TekuaniDebug::Print(TEXT("RTATATAATATATAT"));
		
		float CooldownTime = GetCooldownTimeRemaining();
		if (CooldownTime <= 0.f) CooldownTime = 0.1f;
		
		UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, CooldownTime);
		DelayTask->OnFinish.AddDynamic(this, &UGA_TekuaniMarcela_WeaponFire::FireFullAutoLoop);
		DelayTask->ReadyForActivation();
	}
	else
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_TekuaniMarcela_WeaponFire::FireBurstLoop()
{
	
	if (BurstShotsFired < MaxBurstShots)
	{
		TekuaniDebug::Print(TEXT("3 ratata"));
		PerformHitscan();
		BurstShotsFired++;
		
		UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, BurstDelay);
		DelayTask->OnFinish.AddDynamic(this, &UGA_TekuaniMarcela_WeaponFire::FireBurstLoop);
		DelayTask->ReadyForActivation();
	}
	else
	{
		CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}
