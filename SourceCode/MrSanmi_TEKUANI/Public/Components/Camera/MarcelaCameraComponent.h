#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarcelaCameraComponent.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UMarcelaCombatComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MRSANMI_TEKUANI_API UMarcelaCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMarcelaCameraComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** ===== CONFIG ===== */
	UPROPERTY(EditDefaultsOnly)
	float SwayAmplitude = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float SwaySpeed = 2.f;

	UPROPERTY(EditDefaultsOnly)
	float SwayRecoverySpeed = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float ZoomInterpSpeed = 15.f;

	UPROPERTY(EditDefaultsOnly)
	float DefaultFOV = 90.f;

	UPROPERTY(EditDefaultsOnly)
	float AimFOV = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float DefaultArmLength = 300.f;

	UPROPERTY(EditDefaultsOnly)
	float AimArmLength = 100.f;

	UPROPERTY(EditDefaultsOnly)
	FVector DefaultSocketOffset = FVector(0,0,60);

	UPROPERTY(EditDefaultsOnly)
	FVector AimSocketOffset = FVector(0,60,70);

	/** ===== STATE ===== */
	bool bIsAiming = false;
	float SwayTime = 0.f;

	float CurrentRecoilPitch = 0.f;
	float CurrentRecoilYaw = 0.f;

	FRotator InitialRotation;

	/** ===== REFERENCES ===== */
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	USpringArmComponent* CameraBoom;

	UPROPERTY()
	UMarcelaCombatComponent* CombatComponent;

	/** ===== INTERNAL ===== */
	void UpdateCameraSway(float DeltaTime);
	void UpdateCameraZoom(float DeltaTime);

public:
	/** ===== EVENT HANDLERS ===== */
	UFUNCTION()
	void HandleWeaponFired(float Amount);

	UFUNCTION()
	void HandleAimingChanged(bool bNewAiming);

	void AddSwayKick(float Amount);
};