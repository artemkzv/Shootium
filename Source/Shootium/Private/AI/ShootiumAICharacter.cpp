// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAICharacter.h"
#include "AI/ShootiumAIController.h"

AShootiumAICharacter::AShootiumAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AShootiumAIController::StaticClass();
}
