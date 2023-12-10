// Shootium Game. All Rights Reserved.


#include "Pickups/ShootiumHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AShootiumHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogHealthPickup, Display, TEXT("HealthPickup was taken"));
    return true;
}
