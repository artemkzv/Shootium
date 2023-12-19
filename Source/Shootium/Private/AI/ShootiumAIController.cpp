// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAIController.h"
#include "AI/ShootiumAICharacter.h"
#include "Components/ShootiumAIPerceptionComponent.h"

AShootiumAIController::AShootiumAIController() 
{
    ShootiumAIPerceptionComponent = CreateDefaultSubobject<UShootiumAIPerceptionComponent>("ShootiumPerceptionComponent");
    SetPerceptionComponent(*ShootiumAIPerceptionComponent);
}

void AShootiumAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto ShootiumCharacter = Cast<AShootiumAICharacter>(InPawn);
    if (ShootiumCharacter)
    {
        RunBehaviorTree(ShootiumCharacter->BehaviorTreeAsset);
    }
}

void AShootiumAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    
    const auto AimActor = ShootiumAIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}
