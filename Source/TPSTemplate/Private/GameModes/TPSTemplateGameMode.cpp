#include "GameModes/TPSTemplateGameMode.h"
#include "Characters/TPSTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPSTemplateGameMode::ATPSTemplateGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	ObjectiveComplete.AddDynamic(this, &ATPSTemplateGameMode::OnObjectiveComplete);
}

void ATPSTemplateGameMode::OnEnemyKilled()
{
	EnemiesKilled++;
	LogEnemiesKilled();
}

void ATPSTemplateGameMode::LogEnemiesKilled()
{
	UE_LOG(LogTemp, Warning, TEXT("%i enemies have died"), EnemiesKilled);
}

void ATPSTemplateGameMode::OnObjectiveComplete()
{
}