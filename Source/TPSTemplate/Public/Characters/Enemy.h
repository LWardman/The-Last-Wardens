#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
class UCriticalHitbox;
class ALoot;
class AModifierDrop;

USTRUCT(BlueprintType)
struct FLootTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CommonDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RareDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LegendaryDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ModifierDropChance = 0.0f;

	FLootTable()
	{
		AmmoDropChance = 0.6f;
		CommonDropChance = 0.3f;
		RareDropChance = 0.1f;
		ModifierDropChance = 0.05f;
		LegendaryDropChance = 0.01f;
	}

	FLootTable(float Ammo, float Common, float Rare, float Legendary, float Modifier)
	{
		AmmoDropChance = Ammo;
		CommonDropChance = Common;
		RareDropChance = Rare;
		LegendaryDropChance = Legendary;
		ModifierDropChance = Modifier;
	}

	bool SuccessfulThrow(float Probability)
	{
		return FMath::RandRange(0.0f, 1.0f) <= Probability;
	}
};

UCLASS()
class TPSTEMPLATE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere)
	UCriticalHitbox* CritCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, category = "Components")
	UHealthComponent* Health;

public:

	UPROPERTY(EditAnywhere, Category = "Loot")
	FLootTable LootTable = FLootTable();

	void GenerateLoot();

	void DropLoot();

	UPROPERTY(EditAnywhere, Category = "Loot")
	TSubclassOf<ALoot> AmmoDrop;

	UPROPERTY(EditAnywhere, Category = "Loot")
	TSubclassOf<ALoot> CommonDrop;

	UPROPERTY(EditAnywhere, Category = "Loot")
	TSubclassOf<ALoot> RareDrop;

	UPROPERTY(EditAnywhere, Category = "Loot")
	TSubclassOf<ALoot> LegendaryDrop;

	UPROPERTY(EditAnywhere, Category = "Loot")
	TArray<TSubclassOf<AModifierDrop>> AllModifiers;

	TArray<TSubclassOf<ALoot>> Loot;

public:

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void CallDestroy();

	void StopBehaviorTree();

	void RemoveCollisionForGameplay();

	void StatTrackEnemyDeath();

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;

	FTimerHandle DestructionHandle;

};
