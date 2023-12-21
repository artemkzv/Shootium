// Shootium Game. All Rights Reserved.


#include "AI/Services/ShootiumFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumWeaponComponent.h"

UShootiumFireService::UShootiumFireService() 
{
    NodeName = "Fire";
}

void UShootiumFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    //UE_LOG(LogTemp, Display, TEXT("Find Enemy"));
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Controller = OwnerComp.GetAIOwner();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
