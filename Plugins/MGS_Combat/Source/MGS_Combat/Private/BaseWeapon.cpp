// Copy righted to RAED ABBAS 2023


#include "BaseWeapon.h"

#include "Components/SphereComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootScene);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

