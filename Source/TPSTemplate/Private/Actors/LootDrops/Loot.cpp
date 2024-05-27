#include "Actors/LootDrops/Loot.h"

#include "Components/BoxComponent.h"

ALoot::ALoot()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Collision"));
	BoxCollision->SetupAttachment(Mesh);
}

void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

void ALoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

