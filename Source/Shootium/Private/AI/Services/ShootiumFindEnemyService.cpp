// Shootium Game. All Rights Reserved.


#include "AI/Services/ShootiumFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumAIPerceptionComponent.h"

UShootiumFindEnemyService::UShootiumFindEnemyService() 
{
    NodeName = "Find Enemy";
}

void UShootiumFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
