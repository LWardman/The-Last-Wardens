#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UBehaviorTree;
class UHealthComponent;
class UCriticalHitbox;

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
