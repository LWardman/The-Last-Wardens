#include "Actors/LootDrops/AmmoDrop.h"

#include "Characters/Shooter.h"
#include "Actors/Weapon.h"

void AAmmoDrop::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (AShooter* Player = Cast<AShooter>(OtherActor))
    {
        if (Player->HasWeaponEquipped() && !Player->Weapon->ReserveIsFull())
        {
            Player->Weapon->AddAmmoToReserve(Player->Weapon->ClipSize);
            Destroy();
        }
    }
}