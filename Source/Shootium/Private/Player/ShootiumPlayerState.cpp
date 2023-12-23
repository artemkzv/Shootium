// Shootium Game. All Rights Reserved.


#include "Player/ShootiumPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogShootiumPlayerState, All, All);

void AShootiumPlayerState::LogInfo() 
{
    UE_LOG(LogShootiumPlayerState, Display, TEXT("TeamIF: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
