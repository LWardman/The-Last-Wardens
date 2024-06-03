#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceTracker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSTEMPLATE_API UResourceTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	UResourceTracker();

public:	

	int32 CommonResourceCounter = 0;

	int32 RareResourceCounter = 0;

	int32 LegendaryResourceCounter = 0;

	void IncreaseResourceCounter(int32 &Tracker, int32 NewResourceCount);

	void DecreaseResourceCounter(int32 &Tracker, int32 ResourceReduction);
};
