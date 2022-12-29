// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MGS_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class ABaseCharacter;

protected:
	virtual void BeginPlay() override;

private:
	ABaseCharacter* Character;
	ABaseItem* ReadyItem;
		
};
