#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/ModifierDrop.h"
#include "DamageBuff.generated.h"


UCLASS()
class TPSTEMPLATE_API ADamageBuff : public AModifierDrop
{
	GENERATED_BODY()
	
public:

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;

    float DamageMultiplier = 1.5f;

    float BuffDuration = 30.f;
};
