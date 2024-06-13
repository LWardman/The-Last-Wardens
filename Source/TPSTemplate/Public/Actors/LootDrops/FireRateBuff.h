#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/ModifierDrop.h"
#include "FireRateBuff.generated.h"


UCLASS()
class TPSTEMPLATE_API AFireRateBuff : public AModifierDrop
{
	GENERATED_BODY()
	
protected:

    virtual void BeginPlay() override;

public:

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;

    float FireRateMultiplier = 1.5f;

    float BuffDuration = 30.f;
};
