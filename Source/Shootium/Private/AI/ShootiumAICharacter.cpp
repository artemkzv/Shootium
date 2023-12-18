// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAICharacter.h"
#include "AI/ShootiumAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AShootiumAICharacter::AShootiumAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AShootiumAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}
