// Shootium Game. All Rights Reserved.


#include "UI/ShootiumPlayerHUDWidget.h"
#include "Components/ShootiumHealthComponent.h"
#include "Components/ShootiumWeaponComponent.h"

float UShootiumPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component = Player->GetComponentByClass(UShootiumHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UShootiumHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UShootiumPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UShootiumPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

UShootiumWeaponComponent* UShootiumPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return nullptr;

    const auto Component = Player->GetComponentByClass(UShootiumWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UShootiumWeaponComponent>(Component);
    return WeaponComponent;
}
