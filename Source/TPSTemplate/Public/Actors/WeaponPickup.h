#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponPickup.generated.h"

class UBoxComponent;

class AWeapon;

UCLASS()
class TPSTEMPLATE_API AWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponPickup();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RotatePickup(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float PickupRotationSpeed = 20.f;
};
