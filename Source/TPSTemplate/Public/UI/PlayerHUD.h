#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UImage;

UCLASS()
class TPSTEMPLATE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Crosshair;

	virtual void NativeConstruct();

	void SetCrosshairSize(float Size);
};
