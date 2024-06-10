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

public:	

	AActor* Parent = nullptr;

	UPROPERTY()
	float Modifier = 1.0f;

	FTimerHandle ModifierHandle;

	UFUNCTION()
	void ApplyBuff(float Multiplier, float ModifierDuration);

	UFUNCTION()
	void OnBuffEnd(float OriginalModifier);
};
