#include "FunctionLibrary/MarcelaFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Characters/TekuaniMarcelaCharacter.h"
#include "AnimInstances/Marcela/TekuaniMarcelaAnimInstance.h"
#include "Controllers/TekuaniMarcelaController.h"

UTekuaniMarcelaAnimInstance* UMarcelaFunctionLibrary::GetMarcelaAnimInstance(UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);
	if (!PlayerCharacter) return nullptr;

	ATekuaniMarcelaCharacter* MarcelaCharacter = Cast<ATekuaniMarcelaCharacter>(PlayerCharacter);
	if (!MarcelaCharacter) return nullptr;

	UPaperZDAnimInstance* AnimInstanceBase = MarcelaCharacter->GetMarcelaAnimBPComponent();
	if (!AnimInstanceBase) return nullptr;

	return Cast<UTekuaniMarcelaAnimInstance>(AnimInstanceBase);
}

ATekuaniMarcelaCharacter* UMarcelaFunctionLibrary::GetMarcelaCharacter(UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);
	if (!PlayerCharacter) return nullptr;

	ATekuaniMarcelaCharacter* MarcelaCharacter = Cast<ATekuaniMarcelaCharacter>(PlayerCharacter);
	if (!MarcelaCharacter) return nullptr;

	return MarcelaCharacter;
}

ATekuaniMarcelaController* UMarcelaFunctionLibrary::GetMarcelaController(UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	
	if (!PC) return nullptr;
	
	return Cast<ATekuaniMarcelaController>(PC);
}
