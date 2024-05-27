#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemy;

UCLASS()
class TPSTEMPLATE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnEnemy();


	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> EnemyClass;


	FTimerHandle SpawnHandle;

	float SpawnDelayMin = 2.0f;

	float SpawnDelayMax = 4.0f;
};
