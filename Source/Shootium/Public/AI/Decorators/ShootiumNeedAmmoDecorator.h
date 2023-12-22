// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ShootiumNeedAmmoDecorator.generated.h"

class AShootiumBaseWeapon;

UCLASS()
class SHOOTIUM_API UShootiumNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
    UShootiumNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AShootiumBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
