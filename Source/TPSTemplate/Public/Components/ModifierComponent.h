#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModifierComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSTEMPLATE_API UModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UModifierComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
