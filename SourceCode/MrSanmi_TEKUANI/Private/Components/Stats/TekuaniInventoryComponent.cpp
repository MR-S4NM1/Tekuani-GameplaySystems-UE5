// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Components/Stats/TekuaniInventoryComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "TekuaniDebugHelper.h"
#include "DataAssets/Stats/DA_TekuaniItemStatsData.h"

// Sets default values for this component's properties
UTekuaniInventoryComponent::UTekuaniInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UTekuaniInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTekuaniInventoryComponent::EquipItem(UDA_TekuaniItemStatsData* ItemToEquip)
{
	if (!ItemToEquip) return;
	
	if (EquippedItemEffects.Contains(ItemToEquip)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (!ASC) return;
	
	if (ItemToEquip->ItemStatEffectClass)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ItemToEquip->ItemStatEffectClass, 1.0f, EffectContext);
		
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			
			EquippedItemEffects.Add(ItemToEquip, ActiveHandle);
			
			TekuaniDebug::Print(TEXT("Item Equipado."));
		}
	}
}

void UTekuaniInventoryComponent::UnequipItem(UDA_TekuaniItemStatsData* ItemToUnequip)
{
	if (!ItemToUnequip) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (!ASC) return;
	
	if (FActiveGameplayEffectHandle* HandlePtr = EquippedItemEffects.Find(ItemToUnequip))
	{
		ASC->RemoveActiveGameplayEffect(*HandlePtr);
		
		EquippedItemEffects.Remove(ItemToUnequip);
		TekuaniDebug::Print(TEXT("Item Desequipado."));
	}
}
