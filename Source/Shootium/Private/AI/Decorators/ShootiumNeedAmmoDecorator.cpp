// Shootium Game. All Rights Reserved.


#include "AI/Decorators/ShootiumNeedAmmoDecorator.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumWeaponComponent.h"

UShootiumNeedAmmoDecorator::UShootiumNeedAmmoDecorator() 
{
    NodeName = "Need Ammo";
}

bool UShootiumNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
