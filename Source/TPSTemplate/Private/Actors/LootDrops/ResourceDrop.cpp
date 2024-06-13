#include "Actors/LootDrops/ResourceDrop.h"

#include "Characters/TPSTemplateCharacter.h"
#include "Components/ResourceTracker.h"


void AResourceDrop::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceDrop::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (ATPSTemplateCharacter* Player = Cast<ATPSTemplateCharacter>(OtherActor))
    {
        if (UResourceTracker* Tracker = Player->ResourceTracker)
        {
            if (bIsCommonResource)
            {
                Tracker->IncreaseResourceCounter(Tracker->CommonResourceCounter, ResourceCount);
                Destroy();
            }
            else if (bIsRareResource)
            {
                Tracker->IncreaseResourceCounter(Tracker->RareResourceCounter, ResourceCount);
                Destroy();
            }
            if (bIsLegendaryResource)
            {
                Tracker->IncreaseResourceCounter(Tracker->LegendaryResourceCounter, ResourceCount);
                Destroy();
            }
        }
    }
}