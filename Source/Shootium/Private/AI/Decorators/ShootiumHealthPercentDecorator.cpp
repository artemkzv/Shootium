// Shootium Game. All Rights Reserved.


#include "AI/Decorators/ShootiumHealthPercentDecorator.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumHealthComponent.h"

UShootiumHealthPercentDecorator::UShootiumHealthPercentDecorator() 
{
    NodeName = "Health Percent";
}

bool UShootiumHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
