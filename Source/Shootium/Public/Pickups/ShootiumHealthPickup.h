// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShootiumBasePickup.h"
#include "ShootiumHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTIUM_API AShootiumHealthPickup : public AShootiumBasePickup
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 100.0f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
