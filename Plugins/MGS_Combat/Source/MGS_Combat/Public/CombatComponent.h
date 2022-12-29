// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, AActor*, EquippedItem, bool, bIsEquipped)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MGS_COMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class ABaseCharacter;

protected:
	virtual void BeginPlay() override;

private:
	ABaseCharacter* Character;

	void EquipItem(AActor* ItemToEquip, FName SocketName);

	AActor* CurrentEquippedItem;

	FOnItemEquipped OnItemEquipped;
};
