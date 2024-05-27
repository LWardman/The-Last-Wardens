#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Loot.generated.h"

class UNiagaraSystem;
class UBoxComponent;

UCLASS()
class TPSTEMPLATE_API ALoot : public AActor
{
	GENERATED_BODY()
	
public:	
	ALoot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UNiagaraSystem* LootMarker;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
};
