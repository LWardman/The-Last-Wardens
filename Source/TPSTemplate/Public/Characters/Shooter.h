#pragma once

#include "CoreMinimal.h"
#include "Characters/TPSTemplateCharacter.h"
#include "Shooter.generated.h"


class AWeapon;

UCLASS()
class TPSTEMPLATE_API AShooter : public ATPSTemplateCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

public:
	AShooter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Aim(const FInputActionValue& Value);

	void StopAiming(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void StopFiring(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* Weapon = nullptr;

public:
	void EquipWeapon(TSubclassOf<AWeapon> WeaponClass);

	void UnequipWeapon();

	UFUNCTION(BlueprintCallable)
	bool HasWeaponEquipped();

	UFUNCTION(BlueprintCallable)
	bool IsReloading();

	UFUNCTION()
	void LerpCameraToAimingPosition(float TimeElapsed, float LerpDuration);

	UFUNCTION()
	void LerpCameraToRestingPosition(float TimeElapsed, float LerpDuration);

	UFUNCTION()
	void OnWeaponFired();

	float CalculateWeaponShotSpread();

public:

	FTimerDelegate AimLerpDelegate;

	float RestTargetArmLength = 200.f;
	float AimTargetArmLength = 100.f;

	FVector RestSocketOffset = FVector(0.f, 50.f, 50.f);
	FVector AimSocketOffset = FVector(50.f, 50.f, 50.f);

	UPROPERTY(EditAnywhere)
	float AimLerpDuration = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAimingIn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFiring = false;
};
