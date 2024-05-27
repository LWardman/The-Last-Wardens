#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSTEMPLATE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float DamageTaken);

	void RestoreHealth(float HealthRecovered);

	void SetMaxHealth(float MaxHP);

	void HealToFull();

	AActor* Parent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay Variables")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Gameplay Variables")
	float CurrentHealth = 100.f;

	UPROPERTY(BlueprintAssignable)
	FDeathDelegate Death;
};
