// Shootium Game. All Rights Reserved.


#include "UI/ShootiumPlayerHUDWidget.h"
#include "Components/ShootiumHealthComponent.h"
#include "Components/ShootiumWeaponComponent.h"
#include "ShootiumUtils.h"

bool UShootiumPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UShootiumPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    return Super::Initialize();
}

void UShootiumPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

void UShootiumPlayerHUDWidget::OnNewPawn(APawn* NewPawn) 
{
    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UShootiumPlayerHUDWidget::OnHealthChanged);
    }
}

float UShootiumPlayerHUDWidget::GetHealthPercent() const
{
    
    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UShootiumPlayerHUDWidget::IsPlayerALive() const
{
    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UShootiumPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}



//


bool UShootiumPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UShootiumPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}




