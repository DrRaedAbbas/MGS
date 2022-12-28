// Copy righted to RAED ABBAS 2023


#include "InventorySubsystem.h"

//#include "Components/SphereComponent.h"
//#include "Components/WidgetComponent.h"

UInventorySubsystem::UInventorySubsystem()
{
	/*ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ItemWidget"));
	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphere"));*/
	//ItemSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*ItemSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ItemSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	*///ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnItemOverlapped);
}

void UInventorySubsystem::AddNewItem(AActor* NewItem)
{
	if (NewItem)
	{
		/*NewItem->AddComponentByClass(ItemWidget->StaticClass(), false, NewItem->GetActorTransform(), false);
		NewItem->AddComponentByClass(ItemSphere->StaticClass(), true, NewItem->GetActorTransform(), false);*/
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
		/*if (USphereComponent* tempSphere = Cast<USphereComponent>(NewItem->GetComponentByClass(USphereComponent::StaticClass())))
		{
			tempSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			tempSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			tempSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			tempSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnItemOverlapped);
			tempSphere->SetHiddenInGame(false);
			tempSphere->SetSphereRadius(100);
		}*/
	}
}

//void UInventorySubsystem::OnItemOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OverlappedComponent == ItemSphere)
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(
//				-1,
//				5.f,
//				FColor::Green,
//				TEXT("Overlapped Actor")
//			);
//		}
//	}
//}
