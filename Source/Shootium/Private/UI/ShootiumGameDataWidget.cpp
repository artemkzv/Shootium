// Shootium Game. All Rights Reserved.


#include "UI/ShootiumGameDataWidget.h"
#include "ShootiumGameModeBase.h"
#include "Player/ShootiumPlayerState.h"

int32 UShootiumGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = GetShootiumPlayerState();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UShootiumGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetShootiumGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UShootiumGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetShootiumGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UShootiumGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetShootiumGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}



AShootiumGameModeBase* UShootiumGameDataWidget::GetShootiumGameMode() const 
{
    return GetWorld() ? Cast<AShootiumGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AShootiumPlayerState* UShootiumGameDataWidget::GetShootiumPlayerState() const
{
    return GetOwningPlayer() ? Cast<AShootiumPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
