#include "Actors/LootDrops/FireRateBuff.h"

#include "Characters/Shooter.h"
#include "Actors/Weapon.h"
#include "Components/ModifierComponent.h"

void AFireRateBuff::BeginPlay()
{
	Super::BeginPlay();
}

void AFireRateBuff::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (!OtherActor) return;

    AShooter* Character = Cast<AShooter>(OtherActor);
    if (!Character) return;

    AWeapon* Weapon = Character->Weapon;
    if (!Weapon) return;

    if (UModifierComponent* ModComponent = Weapon->FireRateModifierComponent)
    {
        ModComponent->ApplyBuff(FireRateMultiplier, BuffDuration);
        Destroy();
    }
}