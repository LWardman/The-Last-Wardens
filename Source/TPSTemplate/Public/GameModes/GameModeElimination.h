#pragma once

#include "CoreMinimal.h"
#include "GameModes/TPSTemplateGameMode.h"
#include "GameModeElimination.generated.h"


UCLASS()
class TPSTEMPLATE_API AGameModeElimination : public ATPSTemplateGameMode
{
	GENERATED_BODY()

	AGameModeElimination();
	
	virtual void OnEnemyKilled() override;

	virtual void OnObjectiveComplete() override;

	UPROPERTY(EditAnywhere)
	int32 TargetEliminations = 10;
};
