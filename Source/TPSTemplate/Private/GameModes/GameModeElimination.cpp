#include "GameModes/GameModeElimination.h"

AGameModeElimination::AGameModeElimination()
{

}

void AGameModeElimination::OnEnemyKilled()
{
    Super::OnEnemyKilled();

    if (EnemiesKilled >= TargetEliminations)
    {
        ObjectiveComplete.Broadcast();
        ObjectiveComplete.Clear();
    }
}

void AGameModeElimination::OnObjectiveComplete()
{
    Super::OnObjectiveComplete();
}