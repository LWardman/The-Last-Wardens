#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/Loot.h"
#include "ModifierDrop.generated.h"


UCLASS()
class TPSTEMPLATE_API AModifierDrop : public ALoot
{
	GENERATED_BODY()

public:
	AModifierDrop();

protected:	

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;

	void RotateModifierDrop(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "LERP")
	float RotationSpeed = 15.f;
	
};
