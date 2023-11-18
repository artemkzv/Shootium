// Shootium Game. All Rights Reserved.


#include "ShootiumGameModeBase.h"
#include "Player/ShootiumBaseCharacter.h"
#include "Player/ShootiumPlayerController.h"

AShootiumGameModeBase::AShootiumGameModeBase()
{
    DefaultPawnClass = AShootiumBaseCharacter::StaticClass();
    PlayerControllerClass = AShootiumPlayerController::StaticClass();
}
