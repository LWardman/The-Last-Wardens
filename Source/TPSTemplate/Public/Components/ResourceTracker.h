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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
