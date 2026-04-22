// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Components/ActorComponent.h"
#include "TekuaniInventoryComponent.generated.h"


class UDA_TekuaniItemStatsData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRSANMI_TEKUANI_API UTekuaniInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTekuaniInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#pragma region TekuaniInventoryComponent
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tekuani|Equipment")
	TMap<TObjectPtr<UDA_TekuaniItemStatsData>, FActiveGameplayEffectHandle> EquippedItemEffects;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Equipment")
	void EquipItem(UDA_TekuaniItemStatsData* ItemToEquip);
	
	UFUNCTION(BlueprintCallable, Category = "Tekuani|Equipment")
	void UnequipItem(UDA_TekuaniItemStatsData* ItemToUnequip);
	
#pragma endregion
		
};
