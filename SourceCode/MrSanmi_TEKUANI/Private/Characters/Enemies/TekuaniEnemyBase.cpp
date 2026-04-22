// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved


#include "Characters/Enemies/TekuaniEnemyBase.h"

#include "TekuaniDebugHelper.h"
#include "AbilitySystem/TekuaniAbilitySystemComponent.h"
#include "AbilitySystem/TekuaniAttributeSet.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"


ATekuaniEnemyBase::ATekuaniEnemyBase()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATekuaniEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (TekuaniAbilitySystemComponent && TekuaniAttributeSet)
	{
		TekuaniAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			TekuaniAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &ATekuaniEnemyBase::OnHealthChanged);
	}
}

void ATekuaniEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartUpData.IsNull())
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
			LoadedData->GiveToAbilitySystemComponent(TekuaniAbilitySystemComponent);
}

void ATekuaniEnemyBase::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	FString Msg = FString::Printf(TEXT("Dummy recibió daño. Vida actual: %f"), Data.NewValue);
	TekuaniDebug::Print(Msg);
}
