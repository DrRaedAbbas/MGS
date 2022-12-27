// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class MGS_COMBAT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Details")
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, Category = "Weapon Details")
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Details")
	USkeletalMeshComponent* WeaponMesh;
};
