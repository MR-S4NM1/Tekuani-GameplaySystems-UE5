// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PaperZDAnimationComponent.h"
#include "Enums/TekuaniWeaponFireMode.h"
#include "TekuaniWeaponBase.generated.h"


class UGameplayEffect;

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

USTRUCT(BlueprintType)
struct FTekuaniWeaponCombatStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|DamageEffects")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Recoil")
	float RecoilPitch = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Recoil")
	float RecoilYawRange = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Firing")
	ETekuaniWeaponFireMode FireMode = ETekuaniWeaponFireMode::SemiAuto;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Firing")
	float TraceDistance = 10000.f;
};
