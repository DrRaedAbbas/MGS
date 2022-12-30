// Copy righted to RAED ABBAS 2023


#include "Character/BaseCharacter.h"

#include "BaseItem.h"
#include "CombatComponent.h"
#include "InventoryComponent.h"
#include "ItemPrimaryDataAsset.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	Combat = CreateDefaultSubobject<UCombatComponent>("Combat");
	Combat->SetIsReplicated(true);

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->SetIsReplicated(true);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
		Combat->OnItemEquipped.AddDynamic(this, &ThisClass::OnItemEquippedCompleted);
	}
	if (Inventory)
	{
		Inventory->Character = this;
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ABaseCharacter, OverlappingItem, COND_OwnerOnly);
	DOREPLIFETIME(ABaseCharacter, bItemIsEquipped);
	DOREPLIFETIME(ABaseCharacter, EquipAnimation);
	DOREPLIFETIME(ABaseCharacter, bIsAim);
	DOREPLIFETIME(ABaseCharacter, AimYaw);
	DOREPLIFETIME(ABaseCharacter, AimRoll);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::EquipItem(AActor* ItemToEquip)
{
	if (Combat)
	{
		if (HasAuthority())
		{
			RequestEquipItem(ItemToEquip);
		}
		else
		{
			ServerEquipItem(ItemToEquip);
		}
	}
}
void ABaseCharacter::RequestEquipItem(AActor* ItemToEquip)
{
	ABaseItem* NewItem = nullptr;
	if (ItemToEquip)
	{
		NewItem = Cast<ABaseItem>(ItemToEquip);
	}

	if (OverlappingItem)
	{
		NewItem = Cast<ABaseItem>(OverlappingItem);
	}

	if (NewItem)
	{
		FName SocketName = NewItem->ItemDetails->EquipSocketName;
		Combat->EquipItem(NewItem, SocketName);
//		NewItem->SetItemState(EItemState::E_Equipped);
	}
}
void ABaseCharacter::ServerEquipItem_Implementation(AActor* ItemToEquip)
{
	RequestEquipItem(ItemToEquip);
}
void ABaseCharacter::OnItemEquippedCompleted(AActor* EquippedItem, bool bIsEquipped)
{
	if (ABaseItem* NewItem = Cast<ABaseItem>(EquippedItem))
	{
		NewItem->SetItemState(EItemState::E_Equipped);
		EquipAnimation = NewItem->ItemDetails->ItemEqipingAnimation;
		bItemIsEquipped = bIsEquipped;
		UE_LOG(LogTemp, Warning, TEXT("Item equipped"));
	}
}

void ABaseCharacter::AimItem(bool bNewAim)
{
	ServerAim(bNewAim);
}
void ABaseCharacter::ServerAim_Implementation(bool bIsAimNew)
{
	bIsAim = bIsAimNew;
	if (bIsAim == false)
	{
		AimYaw = 0;
		AimRoll = 0;
	}
}

void ABaseCharacter::AimOffset(float NewAimYaw, float NewAimRoll)
{
	ServerAimOffset(NewAimYaw, NewAimRoll);
}
void ABaseCharacter::ServerAimOffset_Implementation(float AimYawNew, float AimRollNew)
{
	AimYaw = AimYaw + AimYawNew;
	AimRoll = AimRoll + AimRollNew;
}

void ABaseCharacter::OnRep_OverlappingItem(ABaseItem* LastOverlappingItem)
{
	if (OverlappingItem)
	{
		OverlappingItem->ShowItemWidget(true);
	}
	if (LastOverlappingItem)
	{
		LastOverlappingItem->ShowItemWidget(false);
	}
}
void ABaseCharacter::SetOverlappedItem(ABaseItem* NewItem)
{
	if (OverlappingItem)
	{
		if (IsLocallyControlled()) OverlappingItem->ShowItemWidget(false);
	}
	OverlappingItem = NewItem;
	if (IsLocallyControlled())
	{
		if (OverlappingItem == nullptr) return;
		OverlappingItem->ShowItemWidget(true);
	}
}
