#include "Components/HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth; // Ensures all Actors with this HealthComp start at max hp.

	Parent = GetOwner();
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::TakeDamage(float DamageTaken)
{
	CurrentHealth -= DamageTaken;

	if (CurrentHealth < 0)
	{
		Death.Broadcast();
		Death.Clear(); 			// Remove all functions from death delegate so this even only ever broadcasts once.
	}
}

void UHealthComponent::RestoreHealth(float HealthRecovered)
{
	CurrentHealth += HealthRecovered;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::SetMaxHealth(float MaxHP)
{
	MaxHealth = MaxHP;
}

void UHealthComponent::HealToFull()
{
	CurrentHealth = MaxHealth;
}