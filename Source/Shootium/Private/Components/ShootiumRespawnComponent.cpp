// Shootium Game. All Rights Reserved.


#include "Components/ShootiumRespawnComponent.h"
#include "ShootiumGameModeBase.h"

UShootiumRespawnComponent::UShootiumRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShootiumRespawnComponent::Respawn(int32 RespawnTime) 
{
    if (!GetWorld()) return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UShootiumRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void UShootiumRespawnComponent::RespawnTimerUpdate() 
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld())
            return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<AShootiumGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
