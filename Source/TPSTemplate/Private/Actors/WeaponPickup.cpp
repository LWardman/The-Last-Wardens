#include "Actors/WeaponPickup.h"

#include "Components/BoxComponent.h"

#include "Actors/Weapon.h"
#include "Characters/Shooter.h"


AWeaponPickup::AWeaponPickup()
{
 	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(WeaponMesh);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box->SetupAttachment(WeaponMesh);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnBoxOverlapBegin);
}

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotatePickup(DeltaTime);
}

void AWeaponPickup::OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!WeaponClass) return;

	if (AShooter* Character = Cast<AShooter>(OtherActor))
	{
		Character->EquipWeapon(WeaponClass);
	}
}

void AWeaponPickup::RotatePickup(float DeltaTime)
{
	FRotator YawRotation = FRotator(0.f, PickupRotationSpeed, 0.f);

	SetActorRotation(GetActorRotation() + DeltaTime * YawRotation);
}
