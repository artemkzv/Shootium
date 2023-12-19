// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootiumFireService.generated.h"

UCLASS()
class SHOOTIUM_API UShootiumFireService : public UBTService
{
	GENERATED_BODY()
	
public:
    UShootiumFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
