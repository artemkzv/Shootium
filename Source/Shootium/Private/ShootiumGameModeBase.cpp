// Shootium Game. All Rights Reserved.


#include "ShootiumGameModeBase.h"
#include "Player/ShootiumBaseCharacter.h"
#include "Player/ShootiumPlayerController.h"
#include "UI/ShootiumGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogShootiumGameModeBase, All, All);

AShootiumGameModeBase::AShootiumGameModeBase()
{
    DefaultPawnClass = AShootiumBaseCharacter::StaticClass();
    PlayerControllerClass = AShootiumPlayerController::StaticClass();
    HUDClass = AShootiumGameHUD::StaticClass();
}

void AShootiumGameModeBase::StartPlay() 
{
    Super::StartPlay();

    SpawnBots();

    CurrentRound = 1;
    StartRound();
}

UClass* AShootiumGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShootiumGameModeBase::SpawnBots() 
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayerNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto ShootiumAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(ShootiumAIController);
    }
}

void AShootiumGameModeBase::StartRound() 
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShootiumGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AShootiumGameModeBase::GameTimerUpdate() 
{
    UE_LOG(LogShootiumGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound,GameData.RoundsNum);
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            StartRound();
        }
        else
        {
            UE_LOG(LogShootiumGameModeBase, Display, TEXT("======== Game Over ========"));
        }
    }
}
