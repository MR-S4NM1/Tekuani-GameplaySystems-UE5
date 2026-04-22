#include "Components/Camera/MarcelaCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Components/Combat/MarcelaCombatComponent.h"

UMarcelaCameraComponent::UMarcelaCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMarcelaCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		Camera = Owner->FindComponentByClass<UCameraComponent>();
		CameraBoom = Owner->FindComponentByClass<USpringArmComponent>();
		CombatComponent = Owner->FindComponentByClass<UMarcelaCombatComponent>();
	}

	if (Camera)
		InitialRotation = Camera->GetRelativeRotation();
	
	if (CombatComponent)
	{
		CombatComponent->OnWeaponFired.RemoveDynamic(this, &UMarcelaCameraComponent::HandleWeaponFired);
		CombatComponent->OnAimingChanged.RemoveDynamic(this, &UMarcelaCameraComponent::HandleAimingChanged);
		CombatComponent->OnWeaponFired.AddDynamic(this, &UMarcelaCameraComponent::HandleWeaponFired);
		CombatComponent->OnAimingChanged.AddDynamic(this, &UMarcelaCameraComponent::HandleAimingChanged);
	}
}

void UMarcelaCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCameraSway(DeltaTime);
	UpdateCameraZoom(DeltaTime);
}

void UMarcelaCameraComponent::HandleWeaponFired(float Amount)
{
	AddSwayKick(Amount * 0.5f);
}

void UMarcelaCameraComponent::HandleAimingChanged(bool bNewAiming)
{
	bIsAiming = bNewAiming;
}

void UMarcelaCameraComponent::UpdateCameraSway(float DeltaTime)
{
	if (!Camera) return;

	if (!bIsAiming)
	{
		Camera->SetRelativeRotation(
			FMath::RInterpTo(Camera->GetRelativeRotation(), InitialRotation, DeltaTime, SwayRecoverySpeed)
		);
		return;
	}

	SwayTime += DeltaTime * SwaySpeed;

	float X = FMath::Sin(SwayTime) * SwayAmplitude;
	float Y = FMath::Cos(SwayTime * 0.5f) * SwayAmplitude;

	CurrentRecoilPitch = FMath::FInterpTo(CurrentRecoilPitch, 0.f, DeltaTime, SwayRecoverySpeed * 2.f);
	CurrentRecoilYaw   = FMath::FInterpTo(CurrentRecoilYaw, 0.f, DeltaTime, SwayRecoverySpeed * 2.f);

	FRotator Offset(Y + CurrentRecoilPitch, X + CurrentRecoilYaw, 0.f);

	FRotator Target = InitialRotation + Offset;

	Camera->SetRelativeRotation(
		FMath::RInterpTo(Camera->GetRelativeRotation(), Target, DeltaTime, SwayRecoverySpeed)
	);
}

void UMarcelaCameraComponent::AddSwayKick(float Amount)
{
	CurrentRecoilPitch += Amount;
	CurrentRecoilYaw += FMath::RandRange(-Amount * 0.3f, Amount * 0.3f);
}

void UMarcelaCameraComponent::UpdateCameraZoom(float DeltaTime)
{
	if (!Camera || !CameraBoom) return;

	float TargetFOV = bIsAiming ? AimFOV : DefaultFOV;
	float TargetArm = bIsAiming ? AimArmLength : DefaultArmLength;
	FVector TargetOffset = bIsAiming ? AimSocketOffset : DefaultSocketOffset;

	Camera->SetFieldOfView(FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed));
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, TargetArm, DeltaTime, ZoomInterpSpeed);
	CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, TargetOffset, DeltaTime, ZoomInterpSpeed);
}