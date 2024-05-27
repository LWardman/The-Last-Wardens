#include "UI/PlayerHUD.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"


void UPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

}

void UPlayerHUD::SetCrosshairSize(float Size)
{
    if (!Crosshair) return;

    if (UCanvasPanelSlot* ImageSlot = Cast<UCanvasPanelSlot>(Crosshair->Slot))
    {
        ImageSlot->SetSize(FVector2D(Size, Size));
    }
}
