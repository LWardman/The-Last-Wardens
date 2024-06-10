#include "Actors/LootDrops/SpeedBuff.h"

#include "Characters/TPSTemplateCharacter.h"
#include "Components/ModifierComponent.h"

void ASpeedBuff::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (!OtherActor) return;

    if (ATPSTemplateCharacter* Character = Cast<ATPSTemplateCharacter>(OtherActor))
    {
        if (UModifierComponent* ModComponent = Character->SpeedModifierComponent)
        {
            ModComponent->ApplyBuff(SpeedMultiplier, BuffDuration);

            Destroy();
        }
    }
}
