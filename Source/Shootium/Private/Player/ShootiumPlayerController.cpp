// Shootium Game. All Rights Reserved.


#include "Player/ShootiumPlayerController.h"
#include "Components/ShootiumRespawnComponent.h"

AShootiumPlayerController::AShootiumPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<UShootiumRespawnComponent>("RespawnComponent");
}


