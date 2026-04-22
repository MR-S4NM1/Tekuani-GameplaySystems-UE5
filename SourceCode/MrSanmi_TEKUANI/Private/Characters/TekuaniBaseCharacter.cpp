// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Characters/TekuaniBaseCharacter.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "AbilitySystem/TekuaniAttributeSet.h"
#include "Components/Health/TekuaniHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATekuaniBaseCharacter::ATekuaniBaseCharacter()
{
	/**
	 * Tick is disabled by default for performance optimization.
	 *
	 * Since this base class does not implement per-frame logic,
	 * ticking is unnecessary unless explicitly required by child classes.
	 *
	 * Derived classes can enable ticking if they introduce
	 * time-dependent behavior.
	 */
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	TekuaniAbilitySystemComponent = CreateDefaultSubobject<UTekuaniAbilitySystemComponent>(TEXT("TekuaniAbilitySystemComponent"));
	TekuaniAttributeSet = CreateDefaultSubobject<UTekuaniAttributeSet>(TEXT("TekuaniAttributeSet"));
	TekuaniHealthComponent = CreateDefaultSubobject<UTekuaniHealthComponent>("TekuaniHealthComponent");
	
	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSocket"));
	WeaponSocket->SetupAttachment(GetSprite());
}

void ATekuaniBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	BindDelegates();
}

UAbilitySystemComponent* ATekuaniBaseCharacter::GetAbilitySystemComponent() const
{
	return GetTekuaniAbilitySystemComponent();
}

void ATekuaniBaseCharacter::BindDelegates()
{
	
}

void ATekuaniBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (TekuaniAbilitySystemComponent)
	{
		TekuaniAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

bool ATekuaniBaseCharacter::IsCharacterFalling() const
{
	const UCharacterMovementComponent* Movement = GetCharacterMovement();
	return Movement && Movement->IsFalling();
}

void ATekuaniBaseCharacter::HandleDOT_Implementation(float Damage)
{
	if (TekuaniHealthComponent)
		TekuaniHealthComponent->ApplyDamage(Damage);
}

void ATekuaniBaseCharacter::HandleHOT_Implementation(float Heal)
{
	if (TekuaniHealthComponent)
		TekuaniHealthComponent->ApplyHeal(Heal);
}