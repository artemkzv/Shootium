// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAICharacter.h"
#include "AI/ShootiumAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ShootiumAIWeaponComponent.h"
#include "BrainComponent.h"

AShootiumAICharacter::AShootiumAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UShootiumAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AShootiumAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void AShootiumAICharacter::OnDeath() 
{
    Super::OnDeath();

    const auto ShootiumController = Cast<AAIController>(Controller);
    if (ShootiumController && ShootiumController->BrainComponent)
    {
        ShootiumController->BrainComponent->Cleanup();
    }
}
