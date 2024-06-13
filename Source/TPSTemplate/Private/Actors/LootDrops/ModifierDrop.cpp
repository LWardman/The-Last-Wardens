#include "Actors/LootDrops/ModifierDrop.h"


AModifierDrop::AModifierDrop()
{
	bHasLifespan = true;
	Lifespan = 20.f;
}

void AModifierDrop::BeginPlay()
{
	Super::BeginPlay();
}

void AModifierDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RotateModifierDrop(DeltaTime);
}

void AModifierDrop::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                        const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AModifierDrop::RotateModifierDrop(float DeltaTime)
{
	FRotator YawRotation = FRotator(0.f, RotationSpeed, 0.f);

	SetActorRotation(GetActorRotation() + DeltaTime * YawRotation);
}
