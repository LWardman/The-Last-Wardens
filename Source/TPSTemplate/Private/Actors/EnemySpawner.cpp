#include "Actors/EnemySpawner.h"

#include "Characters/Enemy.h"

AEnemySpawner::AEnemySpawner()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	float SpawnDelay = FMath::RandRange(SpawnDelayMin, SpawnDelayMax);

	GetWorld()->GetTimerManager().SetTimer(
		SpawnHandle,
		this,
		&AEnemySpawner::SpawnEnemy,
		SpawnDelay,
		true
	);
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemy()
{
	GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorLocation(), GetActorRotation());
}

