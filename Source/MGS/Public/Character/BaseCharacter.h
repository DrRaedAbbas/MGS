// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MGS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> &OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingItem)
	class ABaseItem* OverlappingItem;

	UFUNCTION()
	void OnRep_OverlappingItem(ABaseItem* LastOverlappingItem);

	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;

public:
	UFUNCTION()
	void SetOverlappedItem(ABaseItem* NewItem);
};
