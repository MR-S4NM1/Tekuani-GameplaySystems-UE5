// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PaperZDAnimationComponent.h"
#include "TekuaniWeaponBase.generated.h"


UCLASS()
class MRSANMI_TEKUANI_API ATekuaniWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATekuaniWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UPaperSpriteComponent* WeaponSprite;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UPaperFlipbookComponent* WeaponFlipbook;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UPaperZDAnimationComponent* WeaponAnimation;

};
