// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShootiumBasePickup.h"
#include "ShootiumAmmoPickup.generated.h"

class AShootiumBaseWeapon;

UCLASS()
class SHOOTIUM_API AShootiumAmmoPickup : public AShootiumBasePickup
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AShootiumBaseWeapon> WeaponType;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
