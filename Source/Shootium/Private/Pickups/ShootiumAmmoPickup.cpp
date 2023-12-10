// Shootium Game. All Rights Reserved.


#include "Pickups/ShootiumAmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AShootiumAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogAmmoPickup, Display, TEXT("AmmoPickup was taken"));
    return true;
}
