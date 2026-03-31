// Miguel Angel Garcia Elizalde and Carlos Diego Salgado Villanueva All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MarcelaFunctionLibrary.generated.h"

class ATekuaniMarcelaCharacter;
class UTekuaniMarcelaAnimInstance;
class ATekuaniMarcelaController;
/**
 * 
 */
UCLASS()
class MRSANMI_TEKUANI_API UMarcelaFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Retrieves Marcela's combat animation instance.
	 *
	 * Handles character lookup, casting, and AnimBP retrieval internally.
	 *
	 * @param WorldContextObject Required for accessing the world.
	 * @return Marcela combat AnimInstance or nullptr if something fails.
	 */
	UFUNCTION(BlueprintCallable, Category = "Marcela", meta = (WorldContext = "WorldContextObject"))
	static UTekuaniMarcelaAnimInstance* GetMarcelaAnimInstance(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "Marcela", meta = (WorldContext = "WorldContextObject"))
	static ATekuaniMarcelaCharacter* GetMarcelaCharacter(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "Marcela", meta = (WorldContext = "WorldContextObject"))
	static ATekuaniMarcelaController* GetMarcelaController(UObject* WorldContextObject);
};
