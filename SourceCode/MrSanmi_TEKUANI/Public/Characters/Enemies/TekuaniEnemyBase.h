// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/TekuaniBaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "TekuaniEnemyBase.generated.h"

/**
 * @class ATekuaniEnemyBase
 * @brief Base class for all the enemies.
 */
UCLASS()
class MRSANMI_TEKUANI_API ATekuaniEnemyBase : public ATekuaniBaseCharacter
{
	GENERATED_BODY()
	
public:
	ATekuaniEnemyBase();
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
};
