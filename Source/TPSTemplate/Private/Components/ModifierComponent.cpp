#include "Components/ModifierComponent.h"

// Sets default values for this component's properties
UModifierComponent::UModifierComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UModifierComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

