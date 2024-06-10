#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/ModifierDrop.h"
#include "SpeedBuff.generated.h"

UCLASS()
class TPSTEMPLATE_API ASpeedBuff : public AModifierDrop
{
	GENERATED_BODY()
	
public:

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;

    float SpeedMultiplier = 1.5f;

    float BuffDuration = 15.f;
};
