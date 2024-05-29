#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/Loot.h"
#include "AmmoDrop.generated.h"


UCLASS()
class TPSTEMPLATE_API AAmmoDrop : public ALoot
{
	GENERATED_BODY()

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;
	
};
