// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventorySubsystem.h"

#include "BaseItem.generated.h"

UCLASS()
class MGS_INVENTORY_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void ShowItemWidget(bool bShowWidget);
	UFUNCTION()
	void SetItemState(EItemState NewItemState);

	UPROPERTY(EditAnywhere, Category = "MGS|Item Details")
	class UItemPrimaryDataAsset* ItemDetails;

	UFUNCTION(BlueprintCallable, Category = "MGS|Inventory")
	void UpdateItemFromDataAsset();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	USkeletalMeshComponent* ItemMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MGS|Item Details")
	class UWidgetComponent* ItemWidget;
	UPROPERTY(/*VisibleAnywhere, Category = "MGS|Item Details"*/)
	FString EquippingSocket = "hand_rSocket";
	

private:
	UInventorySubsystem* InventorySubsystem;

	UPROPERTY(ReplicatedUsing=OnRep_ItemState, EditAnywhere, Category = "MGS|Item Details")
	EItemState ItemState = EItemState::E_Initial;

	UFUNCTION(BlueprintCallable, Category = "MGS|Inventory")
	void UpdateOverlappingCharacter(ACharacter* OverlappingCharacter, bool bIsOverlapping);

	UFUNCTION()
	void OnRep_ItemState();

	UFUNCTION()
	void UpdateItemState();
};
