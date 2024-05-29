#include "Actors/LootDrops/Loot.h"

#include "Components/BoxComponent.h"

ALoot::ALoot()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Collision"));
	BoxCollision->SetupAttachment(Mesh);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot::OnOverlapBegin);
}

void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

void ALoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoot::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
	
}