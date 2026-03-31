// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Components/Camera/MarcelaCameraComponent.h"
#include "Components/Combat/MarcelaCombatComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UMarcelaCameraComponent::UMarcelaCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMarcelaCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
		CameraBoom = OwnerCharacter->FindComponentByClass<USpringArmComponent>();
		MarcelaCombatComponent = OwnerCharacter->FindComponentByClass<UMarcelaCombatComponent>();
	}
	
	if (Camera)
		InitialRotation = Camera->GetRelativeRotation();
}

// Called every frame
void UMarcelaCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateCameraSway(DeltaTime);
	UpdateCameraZoom(DeltaTime);
}

void UMarcelaCameraComponent::UpdateCameraSway(float DeltaTime)
{
	if (!Camera || !MarcelaCombatComponent) return;
	if (!MarcelaCombatComponent->IsAiming())
	{
		Camera->SetRelativeRotation(
			FMath::RInterpTo(
				Camera->GetRelativeRotation(),
				InitialRotation,
				DeltaTime,
				SwayRecoverySpeed
			)
		);
		return;
	}

	// ===== SWAY BASE =====
	SwayTime += DeltaTime * SwaySpeed;

	float BaseSwayX = FMath::Sin(SwayTime) * SwayAmplitude;
	float BaseSwayY = FMath::Cos(SwayTime * 0.5f) * SwayAmplitude;

	FRotator SwayOffset;
	SwayOffset.Yaw = BaseSwayX;
	SwayOffset.Pitch = BaseSwayY;

	// ===== VISUAL RECOIL =====
	CurrentRecoilPitch = FMath::FInterpTo(CurrentRecoilPitch, 0.f, DeltaTime, SwayRecoverySpeed * 2.f);
	CurrentRecoilYaw   = FMath::FInterpTo(CurrentRecoilYaw, 0.f, DeltaTime, SwayRecoverySpeed * 2.f);

	FRotator RecoilOffset;
	RecoilOffset.Pitch = CurrentRecoilPitch;
	RecoilOffset.Yaw   = CurrentRecoilYaw;
	
	FRotator FinalOffset = SwayOffset + RecoilOffset;
	FRotator TargetRotation = InitialRotation + FinalOffset;

	Camera->SetRelativeRotation(
		FMath::RInterpTo(
			Camera->GetRelativeRotation(),
			TargetRotation,
			DeltaTime,
			SwayRecoverySpeed
		)
	);
}

void UMarcelaCameraComponent::AddSwayKick(float Amount)
{
	CurrentRecoilPitch += Amount;
	CurrentRecoilYaw += FMath::RandRange(-Amount * 0.3f, Amount * 0.3f);
}

void UMarcelaCameraComponent::UpdateCameraZoom(float DeltaTime)
{
	if (!Camera || !CameraBoom || !MarcelaCombatComponent) return;

	const bool bIsAiming = MarcelaCombatComponent->IsAiming();

	float TargetFOV = bIsAiming ? AimFOV : DefaultFOV;
	float TargetArmLength = bIsAiming ? AimArmLength : DefaultArmLength;
	FVector TargetSocketOffset = bIsAiming ? AimSocketOffset : DefaultSocketOffset;

	Camera->SetFieldOfView(
		FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed)
	);

	CameraBoom->TargetArmLength = FMath::FInterpTo(
		CameraBoom->TargetArmLength,
		TargetArmLength,
		DeltaTime,
		ZoomInterpSpeed
	);

	CameraBoom->SocketOffset = FMath::VInterpTo(
		CameraBoom->SocketOffset,
		TargetSocketOffset,
		DeltaTime,
		ZoomInterpSpeed
	);
}