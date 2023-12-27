// Shootium Game. All Rights Reserved.


#include "UI/ShootiumSpectatorWidget.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumRespawnComponent.h"

bool UShootiumSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
