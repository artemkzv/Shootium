// Shootium Game. All Rights Reserved.


#include "UI/ShootiumPlayerHUDWidget.h"
#include "Components/ShootiumHealthComponent.h"

float UShootiumPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component = Player->GetComponentByClass(UShootiumHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UShootiumHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}
