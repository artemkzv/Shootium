// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShootiumHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTIUM_API UShootiumHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
    UShootiumHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
