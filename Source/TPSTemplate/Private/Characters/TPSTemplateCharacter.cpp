#include "Characters/TPSTemplateCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/HealthComponent.h"
#include "Components/ResourceTracker.h"
#include "Components/ModifierComponent.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATPSTemplateCharacter::ATPSTemplateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	UseControllerRotation(false);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	Health->Death.AddDynamic(this, &ATPSTemplateCharacter::OnDeath);

	ResourceTracker = CreateDefaultSubobject<UResourceTracker>(TEXT("Resource Tracker"));

	SpeedModifierComponent = CreateDefaultSubobject<UModifierComponent>(TEXT("Speed Modifier Component"));
}

void ATPSTemplateCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATPSTemplateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSTemplateCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSTemplateCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATPSTemplateCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = BaseMovementSpeed * GetSpeedModifier();
	}
}

void ATPSTemplateCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATPSTemplateCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATPSTemplateCharacter::UseControllerRotation(bool newState)
{
	bUseControllerRotationPitch = newState;
	bUseControllerRotationYaw = newState;
	bUseControllerRotationRoll = newState;
}

FHitResult ATPSTemplateCharacter::LineTraceFromCamera(float TraceLength, float TraceSpread)
{
	FHitResult Hit;
	
	if (!FollowCamera) return Hit;
	
	FVector TraceStart = FollowCamera->GetComponentLocation();

	FVector CameraForward = GetFollowCamera()->GetForwardVector();

	FVector CameraRight = GetFollowCamera()->GetRightVector();
	FVector CameraUp = GetFollowCamera()->GetUpVector();

	float RightSpread = FMath::RandRange(-TraceSpread, TraceSpread) / 120.f;	// X-axis spread
	float UpSpread = FMath::RandRange(-TraceSpread, TraceSpread) / 120.f;		// Y-axis spread

	FVector TraceVector = CameraForward + (CameraRight * RightSpread) + (CameraUp * UpSpread);

	FVector TraceEnd = TraceStart + TraceVector * TraceLength;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldDynamic, QueryParams);

	return Hit;
}

void ATPSTemplateCharacter::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s has died"), *GetActorNameOrLabel());
}

float ATPSTemplateCharacter::GetSpeedModifier()
{
	if (!SpeedModifierComponent) return 1.0f;

	return SpeedModifierComponent->Modifier;
}
