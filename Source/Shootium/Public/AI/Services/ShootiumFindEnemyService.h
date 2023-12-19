// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootiumFindEnemyService.generated.h"

UCLASS()
class SHOOTIUM_API UShootiumFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
    UShootiumFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
