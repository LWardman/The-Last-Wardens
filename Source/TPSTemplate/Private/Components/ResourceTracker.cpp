#include "Components/ResourceTracker.h"

UResourceTracker::UResourceTracker()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UResourceTracker::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UResourceTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

