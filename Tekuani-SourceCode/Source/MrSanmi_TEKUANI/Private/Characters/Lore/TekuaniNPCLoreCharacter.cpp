// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#include "Characters/Lore/TekuaniNPCLoreCharacter.h"
#include "Components/SphereComponent.h"

ATekuaniNPCLoreCharacter::ATekuaniNPCLoreCharacter()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(150.f);
	InteractionSphere->SetCollisionProfileName("OverlapAllDynamic");
}

void ATekuaniNPCLoreCharacter::Interact_Implementation(AActor* Interactor)
{
	// Use this for triggering the dialogue system or triggering a shop system.
}
