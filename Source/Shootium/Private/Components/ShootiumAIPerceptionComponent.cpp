// Shootium Game. All Rights Reserved.


#include "Components/ShootiumAIPerceptionComponent.h"
#include "AIController.h"
#include "ShootiumUtils.h"
#include "Components/ShootiumHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UShootiumAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
        return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = ShootiumUtils::GetShootiumPlayerComponent<UShootiumHealthComponent>(PercieveActor);
        if (HealthComponent && !HealthComponent->IsDead()) // TODO: check if enemies or not
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }

    return BestPawn;
}
