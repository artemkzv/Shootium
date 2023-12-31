// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootiumProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UShootiumWeaponFXComponent;

UCLASS()
class SHOOTIUM_API AShootiumProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AShootiumProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleAnyWhere, Category = "Weapon")
    USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnyWhere, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
    UShootiumWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;

private:
    FVector ShotDirection;

	UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;
};
