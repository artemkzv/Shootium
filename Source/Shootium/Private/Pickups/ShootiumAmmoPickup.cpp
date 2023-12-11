// Shootium Game. All Rights Reserved.


#include "Pickups/ShootiumAmmoPickup.h"
#include "Components/ShootiumHealthComponent.h"
#include "Components/ShootiumWeaponComponent.h"
#include "ShootiumUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AShootiumAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
