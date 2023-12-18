// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShootiumAIController.generated.h"

UCLASS()
class SHOOTIUM_API AShootiumAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
    virtual void OnPossess(APawn* InPawn) override;
};
