// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAIController.h"
#include "AI/ShootiumAICharacter.h"

void AShootiumAIController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);

    const auto ShootiumCharacter = Cast<AShootiumAICharacter>(InPawn);
    if (ShootiumCharacter)
    {
        RunBehaviorTree(ShootiumCharacter->BehaviorTreeAsset);
    }
}
