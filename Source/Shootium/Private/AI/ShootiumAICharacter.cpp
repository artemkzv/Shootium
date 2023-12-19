// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAICharacter.h"
#include "AI/ShootiumAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ShootiumAIWeaponComponent.h"

AShootiumAICharacter::AShootiumAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UShootiumAIWeaponComponent>("WeaponComponent"))
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
