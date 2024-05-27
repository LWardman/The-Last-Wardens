#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class TPSTEMPLATE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	void TryReload();

	void Reload();

	void FinishReloading();


	virtual void TryFire();

	virtual void Fire();


	bool ClipIsOutOfAmmo();

	bool ReserveIsOutOfAmmo();


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 ClipSize = 30;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 AmmoCount = ClipSize;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 MaxReserveAmmo = 2 * ClipSize;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 ReserveAmmo = MaxReserveAmmo;


	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float RateOfFire = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float ReloadSpeed = 2.2f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float ShotSpread = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float CriticalModifier = 1.0f; 						// 1.0 adds an additional 100% dmg, 2.0 adds 200% dmg 


	FTimerHandle ShotTimerHandle;

	FTimerHandle ReloadTimerHandle;


	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector MuzzleFlashLocation;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UNiagaraSystem* MuzzleFlashVFX;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* GunshotSFX;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* ReloadSFX;
};
