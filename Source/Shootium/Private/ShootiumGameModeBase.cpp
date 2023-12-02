// Shootium Game. All Rights Reserved.


#include "ShootiumGameModeBase.h"
#include "Player/ShootiumBaseCharacter.h"
#include "Player/ShootiumPlayerController.h"
#include "UI/ShootiumGameHUD.h"

AShootiumGameModeBase::AShootiumGameModeBase()
{
    DefaultPawnClass = AShootiumBaseCharacter::StaticClass();
    PlayerControllerClass = AShootiumPlayerController::StaticClass();
    HUDClass = AShootiumGameHUD::StaticClass();
}
