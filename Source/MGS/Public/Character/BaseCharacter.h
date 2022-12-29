// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseItem;

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

	UFUNCTION(BlueprintCallable, Category="MGS|Combat")
	void EquipItem(AActor* ItemToEquip);

	UFUNCTION()
	void OnItemEquippedCompleted(AActor* EquippedItem, bool bIsEquipped);

private:
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingItem)
	ABaseItem* OverlappingItem;

	UFUNCTION()
	void OnRep_OverlappingItem(ABaseItem* LastOverlappingItem);

	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;

	UFUNCTION(Server, Reliable)
	void ServerEquipItem(AActor* ItemToEquip);

	UFUNCTION()
	void RequestEquipItem(AActor* ItemToEquip);

public:
	UFUNCTION()
	void SetOverlappedItem(ABaseItem* NewItem);

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "MGS|Combat")
	bool bItemIsEquipped = false;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "MGS|Combat")
	UAnimSequence* EquipAnimation;
	
};