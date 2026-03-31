// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Components/Combat/MarcelaCombatComponent.h"

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
	MarcelaCameraComponent = GetOwner()->FindComponentByClass<UMarcelaCameraComponent>();
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

void UMarcelaCombatComponent::TryShoot()
{
	/**
	 * Main shooting entry point.
	 *
	 * Flow:
	 * 1. Validate owner and controller.
	 * 2. Check shooting conditions (aiming, future ammo/cooldowns).
	 * 3. Perform screen-center raycast.
	 * 4. Process hit result.
	 *
	 * Notes:
	 * - Uses viewport center for targeting (TPS aim style).
	 * - Raycast logic may later be moved to a dedicated targeting system.
	 * - Weapon-specific behavior is handled separately.
	 */
	if (!MarcelaCharacter) return;
	
	if (!CanShoot()) return;
	
	int32 ViewportSizeX, ViewportSizeY;
	MarcelaController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	const FVector2D ScreenCenter(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);

	FVector WorldLocation;
	FVector WorldDirection;

	if (MarcelaController->DeprojectScreenPositionToWorld(
		ScreenCenter.X,
		ScreenCenter.Y,
		WorldLocation,
		WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.f);

		FHitResult Hit;

		FCollisionQueryParams Params;
		
		if (CachedPawn.IsValid())
			Params.AddIgnoredActor(CachedPawn.Get());

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			ECC_Visibility,
			Params
		);

		if (bHit)
			OnHit(Hit);
		
		ApplyRecoil(MarcelaController);

#if WITH_EDITOR
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
#endif
	}
}

void UMarcelaCombatComponent::OnHit(const FHitResult& Hit)
{
	AActor* HitActor = Hit.GetActor();

	if (!HitActor) return;

	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
}

bool UMarcelaCombatComponent::CanShoot() const
{
	return bIsAiming; // Also, we need to include more conditions in order to make it clean.
}

void UMarcelaCombatComponent::StartAiming()
{
	if (bIsAiming) return;
	bIsAiming = true;
}

void UMarcelaCombatComponent::StopAiming()
{
	if (!bIsAiming) return;
	bIsAiming = false;
}

bool UMarcelaCombatComponent::IsAiming() const
{
	return bIsAiming;
}

void UMarcelaCombatComponent::ApplyRecoil(APlayerController* PC)
{
	if (!PC) return;

	const float ControlFactor = (1.f - RecoilControl);

	const float Pitch = RecoilPitch * ControlFactor;
	const float Yaw = FMath::RandRange(-RecoilYawRange, RecoilYawRange) * ControlFactor;
	
	TargetRecoil.X = FMath::Clamp(TargetRecoil.X + Pitch, -10.f, 10.f);
	TargetRecoil.Y = FMath::Clamp(TargetRecoil.Y + Yaw, -5.f, 5.f);
	
	if (MarcelaCameraComponent)
		MarcelaCameraComponent->AddSwayKick(Pitch * 0.5f);
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