// Shootium Game. All Rights Reserved.


#include "Pickups/ShootiumHealthPickup.h"
#include "Components/ShootiumHealthComponent.h"
#include "ShootiumUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AShootiumHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
