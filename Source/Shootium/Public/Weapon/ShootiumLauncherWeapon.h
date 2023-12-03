// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "ShootiumLauncherWeapon.generated.h"

class AShootiumProjectile;

UCLASS()
class SHOOTIUM_API AShootiumLauncherWeapon : public AShootiumBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AShootiumProjectile> ProjectileClass;

    virtual void MakeShot() override;
};
