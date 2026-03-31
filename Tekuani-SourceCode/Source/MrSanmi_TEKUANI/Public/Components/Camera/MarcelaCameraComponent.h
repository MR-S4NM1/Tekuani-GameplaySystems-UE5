// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MarcelaCameraComponent.generated.h"

class UMarcelaCombatComponent;
class UCameraComponent;
/**
 * @class UMarcelaCameraComponent
 * @brief Handles camera feedback effects such as sway and recoil for the player.
 *
 * Responsibilities:
 * - Apply camera sway while aiming.
 * - React to combat events (weapon fire, movement).
 * - Enhance game feel without affecting gameplay logic.
 *
 * Notes:
 * - Purely visual system. Does NOT modify gameplay values.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRSANMI_TEKUANI_API UMarcelaCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMarcelaCameraComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** ===== CONFIG ===== */
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwayAmplitude { 1.5f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwaySpeed { 2.f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Sway")
	float SwayRecoverySpeed { 5.f };
	
	/** ===== STATE ===== */
	float SwayTime = 0.f;
	float CurrentSwayKick = 0.f;
	
	/** ===== REFERENCES ===== */
	UPROPERTY()
	UMarcelaCombatComponent* MarcelaCombatComponent;
	
	UPROPERTY()
	UCameraComponent* Camera;
	
	UPROPERTY()
	USpringArmComponent* CameraBoom;

	/** ===== INTERNAL ===== */
	void UpdateCameraSway(float DeltaTime);
	
private:
	/** Camera Configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float DefaultFOV = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float AimFOV = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float DefaultArmLength = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float AimArmLength = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	FVector DefaultSocketOffset = FVector(0.f, 0.f, 60.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	FVector AimSocketOffset = FVector(0.f, 60.f, 70.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed = 15.0f;
	
	FRotator InitialRotation;
	
	/** ===== RECOIL ===== */
	float CurrentRecoilPitch = 0.f;
	float CurrentRecoilYaw = 0.f;
	
public:
	// Called externally (input / combat)
	void AddSwayKick(float Amount);
	
	void UpdateCameraZoom(float DeltaTime);
};
