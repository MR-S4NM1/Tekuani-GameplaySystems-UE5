// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Characters/TekuaniBaseCharacter.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "AbilitySystem/TekuaniAttributeSet.h"

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
	
	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSocket"));
	WeaponSocket->SetupAttachment(GetSprite());
}

UAbilitySystemComponent* ATekuaniBaseCharacter::GetAbilitySystemComponent() const
{
	return GetTekuaniAbilitySystemComponent();
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
