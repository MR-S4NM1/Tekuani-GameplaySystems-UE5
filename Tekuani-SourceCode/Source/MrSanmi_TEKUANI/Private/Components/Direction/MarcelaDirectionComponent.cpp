#include "Components/Direction/MarcelaDirectionComponent.h"
#include "Characters/TekuaniMarcelaCharacter.h"

UMarcelaDirectionComponent::UMarcelaDirectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMarcelaDirectionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMarcelaDirectionComponent::UpdateDirection(ATekuaniMarcelaCharacter* OwnerCharacter)
{
	if (!OwnerCharacter) return;

	FVector Velocity = OwnerCharacter->GetVelocity();
	Velocity.Z = 0.f;

	if (Velocity.SizeSquared() < 1.f) return;
	
	FRotator ControlRot = OwnerCharacter->GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	FVector Forward = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::X);
	FVector Right   = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y);

	FVector VelNorm = Velocity.GetSafeNormal();

	float ForwardDot = FVector::DotProduct(VelNorm, Forward);
	float RightDot   = FVector::DotProduct(VelNorm, Right);

	EMarcelaDirection NewDirection;

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
		NewDirection = ForwardDot > 0 ? EMarcelaDirection::Back : EMarcelaDirection::Front;
	else
		NewDirection = RightDot > 0 ? EMarcelaDirection::Right : EMarcelaDirection::Left;
	
	if (NewDirection != CurrentDirection)
	{
		CurrentDirection = NewDirection;
		OnDirectionChanged.Broadcast(CurrentDirection);
	}
}

FVector2D UMarcelaDirectionComponent::GetDirectionForAnim() const
{
	/**
	 * Converts enum direction into 2D vector representation.
	 *
	 * This mapping is used by PaperZD's SetDirectionality system.
	 */
	switch (CurrentDirection)
	{
	case EMarcelaDirection::Front:
		return FVector2D(0.f, -1.f);

	case EMarcelaDirection::Back:
		return FVector2D(0.f, 1.f);

	case EMarcelaDirection::Left:
		return FVector2D(-1.f, 0.f);

	case EMarcelaDirection::Right:
		return FVector2D(1.f, 0.f);
	}

	return FVector2D::ZeroVector;
}