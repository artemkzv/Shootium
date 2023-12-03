// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "ShootiumRifleWeapon.generated.h"


UCLASS()
class SHOOTIUM_API AShootiumRifleWeapon : public AShootiumBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float TimeBetweenShot = 0.1f;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;
};
