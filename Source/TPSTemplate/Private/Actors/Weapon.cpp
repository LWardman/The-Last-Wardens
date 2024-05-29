#include "Actors/Weapon.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

AWeapon::AWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::TryReload()
{
	if (AmmoCount == ClipSize) return; 			// if weapon is at max capacity

	if (ReserveIsOutOfAmmo()) return;				// if there is no ammo available to put in

	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadTimerHandle)) return;	// if already reloading
	
	Reload();
}

void AWeapon::Reload()
{
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&AWeapon::FinishReloading,
		ReloadSpeed,
		false
	);

	if (ReloadSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSFX, GetActorLocation(), 1.f, 1.f, 0.7f);
	}
}

void AWeapon::FinishReloading()
{
	int32 AmmoNeeded = ClipSize - AmmoCount;					// e.g clip of 30 has 18 bullets left... reload 12

	int32 ReloadCount = FMath::Min(AmmoNeeded, ReserveAmmo);	// Ensures we don't reload more ammo than we have
	
	ReserveAmmo -= ReloadCount;									// transfers ammo out of the reserve... 
	AmmoCount += ReloadCount;									// ... and into the weapon
}

void AWeapon::TryFire()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadTimerHandle)) return;	// if reloading

	if (GetWorld()->GetTimerManager().IsTimerActive(ShotTimerHandle)) return;	// if shot too recently
	
	if (ClipIsOutOfAmmo())
	{
		TryReload();
		return;
	}
	
	Fire();
}

void AWeapon::Fire()
{
	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, RateOfFire, false);

	AmmoCount--;

	UWorld* World = GetWorld();

	if (World && MuzzleFlashVFX)
	{
		FTransform WeaponTransform = GetActorTransform();

        FRotator SpawnRotation = WeaponTransform.Rotator();
		FVector SpawnLocation = WeaponTransform.TransformPosition(MuzzleFlashLocation);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, MuzzleFlashVFX, SpawnLocation, SpawnRotation);
	}

	if (GunshotSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GunshotSFX, GetActorLocation());
	}
}

bool AWeapon::ClipIsOutOfAmmo()
{
	return AmmoCount <= 0;
}

bool AWeapon::ReserveIsOutOfAmmo()
{
	return ReserveAmmo <= 0;
}

bool AWeapon::ReserveIsFull()
{
	return ReserveAmmo == MaxReserveAmmo;
}

void AWeapon::AddAmmoToReserve(int32 AmmoAdded)
{
	ReserveAmmo = FMath::Min(MaxReserveAmmo, ReserveAmmo + AmmoAdded);
}
