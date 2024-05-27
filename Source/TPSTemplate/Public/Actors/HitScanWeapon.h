#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"
#include "HitScanWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFired);

UCLASS()
class TPSTEMPLATE_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void Fire();

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FWeaponFired WeaponFired;

};
