// Shootium Game. All Rights Reserved.


#include "AI/ShootiumAIController.h"
#include "AI/ShootiumAICharacter.h"
#include "Components/ShootiumAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AShootiumAIController::AShootiumAIController() 
{
    ShootiumAIPerceptionComponent = CreateDefaultSubobject<UShootiumAIPerceptionComponent>("ShootiumPerceptionComponent");
    SetPerceptionComponent(*ShootiumAIPerceptionComponent);

    bWantsPlayerState = true;
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
    
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* AShootiumAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
