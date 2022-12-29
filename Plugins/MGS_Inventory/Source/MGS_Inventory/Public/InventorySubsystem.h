// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "InventorySubsystem.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
	E_Initial UMETA(DisplayName = "Initial"),
	E_PickedUp UMETA(DisplayName = "Pickedup"),
	E_Dropped UMETA(DisplayName = "Dropped")
};


UCLASS()
class MGS_INVENTORY_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UInventorySubsystem();

	UFUNCTION(BlueprintCallable, Category="MGS|Inventory")
	void AddNewItem(AActor* NewItem);

private:
	UPROPERTY()
	TArray<AActor*> Items;
};
