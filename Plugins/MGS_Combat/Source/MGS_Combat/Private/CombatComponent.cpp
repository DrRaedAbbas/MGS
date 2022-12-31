// Copy righted to RAED ABBAS 2023


#include "CombatComponent.h"

#include "Character/BaseCharacter.h"
#include "Engine/SkeletalMeshSocket.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCombatComponent::EquipItem(AActor* ItemToEquip, FName SocketName)
{
	if (Character == nullptr || ItemToEquip == nullptr || CurrentEquippedItem) return;
	const USkeletalMeshSocket* Socket = Character->GetMesh()->GetSocketByName(SocketName);
	if (Socket)
	{
		CurrentEquippedItem = ItemToEquip;
		bool bEquipSuccess = Socket->AttachActor(CurrentEquippedItem, Character->GetMesh());
		CurrentEquippedItem->SetOwner(Character);
		OnItemEquipped.Broadcast(CurrentEquippedItem, bEquipSuccess);
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
