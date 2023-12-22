// Shootium Game. All Rights Reserved.


#include "ShootiumGameModeBase.h"
#include "Player/ShootiumBaseCharacter.h"
#include "Player/ShootiumPlayerController.h"
#include "UI/ShootiumGameHUD.h"
#include "AIController.h"

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
