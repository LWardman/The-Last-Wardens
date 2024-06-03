#include "Components/ResourceTracker.h"

UResourceTracker::UResourceTracker()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UResourceTracker::IncreaseResourceCounter(int32 &Tracker, int32 NewResourceCount)
{
	Tracker += NewResourceCount;
}

void UResourceTracker::DecreaseResourceCounter(int32 &Tracker, int32 ResourceReduction)
{
	Tracker -= ResourceReduction;
}
