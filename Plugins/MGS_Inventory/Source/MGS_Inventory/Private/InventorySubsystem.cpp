// Copy righted to RAED ABBAS 2023


#include "InventorySubsystem.h"

UInventorySubsystem::UInventorySubsystem()
{
}

void UInventorySubsystem::AddNewItem(AActor* NewItem)
{
	if (NewItem)
	{
		Items.Add(NewItem);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Green,
				TEXT("New Item Added")
			);
		}
	}
}