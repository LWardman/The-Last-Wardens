#include "Components/ModifierComponent.h"


UModifierComponent::UModifierComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Parent = GetOwner();
}

void UModifierComponent::ApplyBuff(float Multiplier, float ModifierDuration)
{
	if (!Parent || Multiplier == 0) return; 	// Ensures Speed can get back to its previous value OnBuffEnd

	if (UWorld* World = Parent->GetWorld())
	{
		Modifier *= Multiplier;			// Has no dependence on World being valid, but is here to ensure the timer can be set

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "OnBuffEnd", Multiplier);

		World->GetTimerManager().SetTimer(
			ModifierHandle,
			Delegate,
			ModifierDuration,
			false);
	}
}

void UModifierComponent::OnBuffEnd(float OriginalModifier)
{
	Modifier /= OriginalModifier;
}
