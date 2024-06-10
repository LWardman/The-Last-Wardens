#include "Characters/Shooter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "Actors/Weapon.h"
#include "Actors/HitScanWeapon.h"
#include "Components/HealthComponent.h"
#include "UI/PlayerHUD.h"
#include "Components/CriticalHitbox.h"

AShooter::AShooter()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCameraBoom()->TargetArmLength = RestTargetArmLength;
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (PlayerHUDClass)
		{
			PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
			
			if (PlayerHUD)
			{
				PlayerHUD->AddToPlayerScreen();
			}
		}
	}
}

void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerHUD)
	{
		PlayerHUD->SetCrosshairSize(100.f + CalculateWeaponShotSpread() * 8.f); 	// Keeps crosshair size relative to shot spread.
	}
}

void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShooter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShooter::StopAiming);

		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AShooter::Fire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AShooter::StopFiring);

		// Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AShooter::Reload);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AShooter::Aim(const FInputActionValue& Value)
{
	bAimingIn = true;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	float CurrentArmLength = GetCameraBoom()->TargetArmLength;
	float DecimalPercentageComplete = (RestTargetArmLength - CurrentArmLength) / (RestTargetArmLength - AimTargetArmLength);
	float TimeToStartLerpAt = DecimalPercentageComplete * AimLerpDuration;

	LerpCameraToAimingPosition(TimeToStartLerpAt, AimLerpDuration);
	UseControllerRotation(true);
}

void AShooter::StopAiming(const FInputActionValue& Value)
{
	bAimingIn = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	float CurrentArmLength = GetCameraBoom()->TargetArmLength;
	float DecimalPercentageComplete = (CurrentArmLength - AimTargetArmLength) / (RestTargetArmLength - AimTargetArmLength);
	float TimeToStartLerpAt = DecimalPercentageComplete * AimLerpDuration;

	LerpCameraToRestingPosition(TimeToStartLerpAt, AimLerpDuration);
	UseControllerRotation(false);
}

void AShooter::Fire(const FInputActionValue& Value)
{
	UseControllerRotation(true);

	if (HasWeaponEquipped())
	{
		Weapon->TryFire();
	}
}

void AShooter::StopFiring(const FInputActionValue& Value)
{
	if (!bAimingIn)
	{
		UseControllerRotation(false);
	}

	bIsFiring = false;
}

void AShooter::Reload(const FInputActionValue& Value)
{
	if (HasWeaponEquipped())
	{
		Weapon->TryReload();
	}
}

void AShooter::EquipWeapon(TSubclassOf<AWeapon> WeaponClass)
{
	if (!WeaponClass) return;

	if (HasWeaponEquipped()) 
	{
		UnequipWeapon();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
	SpawnParams.Instigator = this;

	Weapon = GetWorld()->SpawnActor<AWeapon>(
		WeaponClass,
		GetActorLocation(),
		GetActorRotation(),
		SpawnParams
		);

	FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		true
		);

	Weapon->AttachToComponent(GetMesh(), AttachmentRules, "RightHandGripPoint");
	
	if (AHitScanWeapon* HitScanWeapon = Cast<AHitScanWeapon>(Weapon))
	{
		HitScanWeapon->WeaponFired.AddDynamic(this, &AShooter::OnWeaponFired);
	}
}

void AShooter::UnequipWeapon()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)	// WARNING : WILL ONLY WORK WHILE WEAPONS ARE THE ONLY ATTACHED ACTORS
	{
		Actor->Destroy();
	}
	Weapon = nullptr;
}

bool AShooter::HasWeaponEquipped()
{
	return Weapon != nullptr;
}

bool AShooter::IsReloading()
{
	if (Weapon == nullptr) return false;

	return GetWorld()->GetTimerManager().IsTimerActive(Weapon->ReloadTimerHandle);
}

void AShooter::LerpCameraToAimingPosition(float TimeElapsed, float LerpDuration)
{
	if (TimeElapsed < LerpDuration && bAimingIn)
	{
		TimeElapsed += GetWorld()->GetDeltaSeconds();

		GetCameraBoom()->TargetArmLength = FMath::Lerp(RestTargetArmLength, AimTargetArmLength, TimeElapsed/LerpDuration);

		GetCameraBoom()->SocketOffset = FMath::Lerp(RestSocketOffset, AimSocketOffset, TimeElapsed/LerpDuration);

		AimLerpDelegate.BindUFunction(this, FName("LerpCameraToAimingPosition"), TimeElapsed, LerpDuration);
		GetWorld()->GetTimerManager().SetTimerForNextTick(AimLerpDelegate);
	}
}

void AShooter::LerpCameraToRestingPosition(float TimeElapsed, float LerpDuration)
{
	if (TimeElapsed < LerpDuration && !bAimingIn)
	{
		TimeElapsed += GetWorld()->GetDeltaSeconds();

		GetCameraBoom()->TargetArmLength = FMath::Lerp(AimTargetArmLength, RestTargetArmLength, TimeElapsed/LerpDuration);

		GetCameraBoom()->SocketOffset = FMath::Lerp(AimSocketOffset, RestSocketOffset, TimeElapsed/LerpDuration);

		AimLerpDelegate.BindUFunction(this, FName("LerpCameraToRestingPosition"), TimeElapsed, LerpDuration);
		GetWorld()->GetTimerManager().SetTimerForNextTick(AimLerpDelegate);
	}
}

void AShooter::OnWeaponFired()
{
	if (!HasWeaponEquipped()) return;

	bIsFiring = true;

	float OverallShotPenalty = CalculateWeaponShotSpread();

	FHitResult Hit = LineTraceFromCamera(10000.f, OverallShotPenalty);

	bool bCriticalHit = false;

	if (Hit.GetComponent() && Hit.GetComponent()->IsA(UCriticalHitbox::StaticClass()))
	{
		bCriticalHit = true;
	}

	if (!Hit.bBlockingHit) return;

	if (UHealthComponent* HealthComp = Cast<UHealthComponent>(Hit.GetActor()->FindComponentByClass(UHealthComponent::StaticClass())))
	{
		HealthComp->TakeDamage(Weapon->CalculateDamageOutput(bCriticalHit));
	}
}

float AShooter::CalculateWeaponShotSpread()
{
	if (!HasWeaponEquipped()) return 0.f;

	float BaseShotSpread = Weapon->ShotSpread;

	float MovementShotPenalty =  GetCharacterMovement()->Velocity.Size() / 75.f;

	float AerialShotPenalty = GetCharacterMovement()->IsFalling() * 3.f;

	return BaseShotSpread + MovementShotPenalty + AerialShotPenalty;
}

