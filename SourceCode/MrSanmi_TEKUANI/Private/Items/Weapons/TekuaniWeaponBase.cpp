// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Items/Weapons/TekuaniWeaponBase.h"

#include "Items/Weapons/TekuaniMarcelaWeapon.h"

// Sets default values
ATekuaniWeaponBase::ATekuaniWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("WeaponSprite"));
	SetRootComponent(WeaponSprite);
	WeaponSprite->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipBook"));
	WeaponFlipbook->SetupAttachment(GetRootComponent());
	WeaponFlipbook->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	WeaponAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("WeaponAnimation"));

}


