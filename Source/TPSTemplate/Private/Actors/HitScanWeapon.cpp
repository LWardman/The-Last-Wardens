#include "Actors/HitScanWeapon.h"

#include "Engine/World.h"


void AHitScanWeapon::Fire()
{
    Super::Fire();
    WeaponFired.Broadcast();
}
