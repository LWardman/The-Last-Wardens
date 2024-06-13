#pragma once

#include "CoreMinimal.h"
#include "Actors/LootDrops/Loot.h"
#include "ResourceDrop.generated.h"


UCLASS()
class TPSTEMPLATE_API AResourceDrop : public ALoot
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	
    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, Category = "Resource Stats")
	bool bIsCommonResource = false;

	UPROPERTY(EditAnywhere, Category = "Resource Stats")
	bool bIsRareResource = false;

	UPROPERTY(EditAnywhere, Category = "Resource Stats")
	bool bIsLegendaryResource = false;

	UPROPERTY(EditAnywhere, Category = "Resource Stats")
	int32 ResourceCount = 0;
};
