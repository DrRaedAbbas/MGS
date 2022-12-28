// Copy righted to RAED ABBAS 2023


#include "Character/BaseCharacter.h"

#include "BaseItem.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ABaseCharacter, OverlappingItem, COND_OwnerOnly);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

