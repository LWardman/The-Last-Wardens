#include "Characters/Enemy.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Components/HealthComponent.h"
#include "Components/CriticalHitbox.h"
#include "Controllers/EnemyController.h"
#include "GameModes/TPSTemplateGameMode.h"
#include "Actors/LootDrops/Loot.h"
#include "Actors/LootDrops/ModifierDrop.h"

AEnemy::AEnemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	CritCollision = CreateDefaultSubobject<UCriticalHitbox>(TEXT("Critical Hitbox Component"));
	CritCollision->SetupAttachment(GetMesh(), TEXT("head"));

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	Health->Death.AddDynamic(this, &AEnemy::OnDeath);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GenerateLoot();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::GenerateLoot()
{
	if (LootTable.SuccessfulThrow(LootTable.AmmoDropChance)) 		Loot.Add(AmmoDrop);
	if (LootTable.SuccessfulThrow(LootTable.CommonDropChance)) 		Loot.Add(CommonDrop);
	if (LootTable.SuccessfulThrow(LootTable.RareDropChance)) 		Loot.Add(RareDrop);
	if (LootTable.SuccessfulThrow(LootTable.LegendaryDropChance)) 	Loot.Add(LegendaryDrop);

	if (LootTable.SuccessfulThrow(LootTable.ModifierDropChance))
	{
		if (AllModifiers.IsEmpty()) return;

		int32 MaxRandRange = AllModifiers.Num() - 1;				// -1 adjusts for index starting at 0

		int32 ModifierIndex = FMath::RandRange(0, MaxRandRange);	// Used to select random entry in TArray

		if (AllModifiers.IsValidIndex(ModifierIndex))
		{
			Loot.Add(AllModifiers[ModifierIndex]);
		}
	}
}

void AEnemy::DropLoot()
{
	for (TSubclassOf<ALoot> LootClass : Loot)
	{
		if (LootClass)
		{
			GetWorld()->SpawnActor<ALoot>(LootClass, GetActorLocation(), GetActorRotation());
		}
	}
}

void AEnemy::OnDeath()
{
	bIsDead = true; 						// This value is read in the animation blueprint.

	StopBehaviorTree(); 					// Enemy no longer needs any defining behavior

	RemoveCollisionForGameplay();			// Allows enemies, players, bullets etc.. to pass through this collision

	StatTrackEnemyDeath();					// Reports death, useful for elimination game mode

	GetWorld()->GetTimerManager().SetTimer(
		DestructionHandle,
		this,
		&AEnemy::CallDestroy,
		10.f,
		false);

	DropLoot();
}

void AEnemy::CallDestroy()
{
	this->Destroy();
}

void AEnemy::StopBehaviorTree()
{
	if (AEnemyController* Ctrl = Cast<AEnemyController>(GetController()))
	{
		Ctrl->StopBehaviorTree();
	}
}

void AEnemy::RemoveCollisionForGameplay()
{
	if (UCapsuleComponent* Collision = GetCapsuleComponent())
	{
		Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block); // Stops enemies falling through the floor on death
	}
}

void AEnemy::StatTrackEnemyDeath()
{
	if (ATPSTemplateGameMode* GameMode = Cast<ATPSTemplateGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnEnemyKilled();
	}
}
