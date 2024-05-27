#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
class UCriticalHitbox;

USTRUCT(BlueprintType)
struct FLootTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CommonDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RareDropChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LegendaryDropChance = 0.0f;

	FLootTable()
	{
		AmmoChance = 0.6f;
		CommonDropChance = 0.3f;
		RareDropChance = 0.05f;
		LegendaryDropChance = 0.005f;
	}

	FLootTable(float Ammo, float Common, float Rare, float Legendary)
	{
		AmmoChance = Ammo;
		CommonDropChance = Common;
		RareDropChance = Rare;
		LegendaryDropChance = Legendary;
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

	UPROPERTY(EditAnywhere)
	FLootTable LootTable = FLootTable();

	void GenerateLoot();

	//UPROPERTY(EditAnywhere)
	//TArray<class ALoot*> Loot;

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void CallDestroy();

	void StopBehaviorTree();

	void RemoveCollisionForGameplay();

	void StatTrackEnemyDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDead = false;

	FTimerHandle DestructionHandle;

};
