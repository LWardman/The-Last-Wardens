#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSTemplateGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObjectiveCompleteDelegate);

UCLASS(minimalapi)
class ATPSTemplateGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSTemplateGameMode();

	virtual void OnEnemyKilled();

	void LogEnemiesKilled();

	UFUNCTION()
	virtual void OnObjectiveComplete();

	int32 EnemiesKilled = 0;

	UPROPERTY(BlueprintAssignable)
	FObjectiveCompleteDelegate ObjectiveComplete;


};
