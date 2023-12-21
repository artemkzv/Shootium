// Shootium Game. All Rights Reserved.

#include "AI/Services/ShootiumChangeWeaponService.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumWeaponComponent.h"

UShootiumChangeWeaponService::UShootiumChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UShootiumChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
