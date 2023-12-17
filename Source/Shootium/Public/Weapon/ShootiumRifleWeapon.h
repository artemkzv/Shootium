// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "ShootiumRifleWeapon.generated.h"

class UShootiumWeaponFXComponent;
class UNiagaraComponent;

UCLASS()
class SHOOTIUM_API AShootiumRifleWeapon : public AShootiumBaseWeapon
{
	GENERATED_BODY()
	
public:
    AShootiumRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShot = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UShootiumWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    void MakeDamage(const FHitResult& HitResult);
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
};
