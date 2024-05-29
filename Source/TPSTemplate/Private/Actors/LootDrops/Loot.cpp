#include "Actors/LootDrops/Loot.h"

#include "Components/BoxComponent.h"

#include "NiagaraFunctionLibrary.h"

ALoot::ALoot()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYRotation = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(Mesh);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot::OnOverlapBegin);
}

void ALoot::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && LootMarker && Mesh)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached
			( 
			LootMarker,
			RootComponent,
			FName("None"),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition,
			true, //unsure
			true, //unsure
			ENCPoolMethod::None,
			true //unsure
			);
	}
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