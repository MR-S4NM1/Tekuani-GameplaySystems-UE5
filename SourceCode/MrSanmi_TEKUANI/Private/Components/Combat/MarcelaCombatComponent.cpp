// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Components/Combat/MarcelaCombatComponent.h"

#include "TekuaniDebugHelper.h"
#include "Characters/TekuaniMarcelaCharacter.h"
#include "Items/Weapons/TekuaniMarcelaWeapon.h"
#include "Components/Camera/MarcelaCameraComponent.h"
#include "Controllers/TekuaniMarcelaController.h"

UMarcelaCombatComponent::UMarcelaCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UMarcelaCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(true);
	
	/**
	 * Cache owning pawn to avoid repeated casting during shooting logic.
	 * This reduces overhead in high-frequency gameplay functions.
	 */
	CachedPawn = Cast<APawn>(GetOwner());
	MarcelaCharacter = Cast<ATekuaniMarcelaCharacter>(CachedPawn.Get());
	MarcelaController = CachedPawn.IsValid() ? Cast<ATekuaniMarcelaController>(CachedPawn->GetController()) : nullptr;
}

void UMarcelaCombatComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRecoil(DeltaTime);
}


ATekuaniMarcelaWeapon* UMarcelaCombatComponent::GetMarcelaCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ATekuaniMarcelaWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UMarcelaCombatComponent::StartAiming()
{
	if (bIsAiming) return;
	bIsAiming = true;
	
	if (OnAimingChanged.IsBound())
		OnAimingChanged.Broadcast(true);
}

void UMarcelaCombatComponent::StopAiming()
{
	if (!bIsAiming) return;
	bIsAiming = false;
	
	if (OnAimingChanged.IsBound())
		OnAimingChanged.Broadcast(false);
}

void UMarcelaCombatComponent::CycleFireMode()
{
	if (!CurrentWeaponDefinition || !CurrentWeaponDefinition->FireModesData) return;
	
	int32 TotalModes = CurrentWeaponDefinition->FireModesData->AvailableFireModes.Num();
	if (TotalModes <= 1) return;
	
	ATekuaniMarcelaWeapon* EquippedWeapon = GetMarcelaCarriedWeaponByTag(CurrentWeaponDefinition->BaseData->WeaponTag);
	
	if (EquippedWeapon)
	{
		int32 CurrentIndex = EquippedWeapon->GetCurrentFireModeIndex();
		int32 NextIndex = (CurrentIndex + 1) % TotalModes;
		
		EquippedWeapon->SetCurrentFireModeIndex(NextIndex);
		
		ETekuaniWeaponFireMode NewMode = CurrentWeaponDefinition->FireModesData->AvailableFireModes[NextIndex].FireMode;
		FString ModeName = UEnum::GetValueAsString(NewMode);
		FString Msg = FString::Printf(TEXT("Modo de disparo: %s"), *ModeName);
		TekuaniDebug::Print(Msg);
	}
}

bool UMarcelaCombatComponent::IsAiming() const
{
	return bIsAiming;
}

void UMarcelaCombatComponent::ApplyRecoil(FWeaponRecoilData& RecoilData)
{
	RecoilPitch = RecoilData.RecoilPitch;
	RecoilYawRange = RecoilData.RecoilYawRange;
	RecoilControl = RecoilData.RecoilControl;
	RecoilDamping = RecoilData.RecoilDamping;
	RecoilReturnSpeed = RecoilData.RecoilReturnSpeed;
	
	const float ControlFactor = (1.f - RecoilControl);

	const float Pitch = RecoilPitch * ControlFactor;
	const float Yaw = FMath::RandRange(-RecoilYawRange, RecoilYawRange) * ControlFactor;
	
	TargetRecoil.X = FMath::Clamp(TargetRecoil.X + Pitch, -10.f, 10.f);
	TargetRecoil.Y = FMath::Clamp(TargetRecoil.Y + Yaw, -5.f, 5.f);;
}

void UMarcelaCombatComponent::UpdateRecoil(float DeltaTime)
{
	TargetRecoil = FMath::Vector2DInterpTo(
		TargetRecoil,
		FVector2D::ZeroVector,
		DeltaTime,
		RecoilReturnSpeed
	);
	
	CurrentRecoil = FMath::Vector2DInterpTo(
		CurrentRecoil,
		TargetRecoil,
		DeltaTime,
		RecoilDamping
	);
	
	FVector2D Delta = CurrentRecoil - LastFrameRecoil;
	LastFrameRecoil = CurrentRecoil;
	
	if (CachedPawn.IsValid())
	{
		if (APlayerController* PC = Cast<APlayerController>(CachedPawn->GetController()))
		{
			PC->AddPitchInput(-Delta.X);
			PC->AddYawInput(Delta.Y);
		}
	}
}