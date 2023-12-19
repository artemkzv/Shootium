// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShootiumAIController.generated.h"

class UShootiumAIPerceptionComponent;

UCLASS()
class SHOOTIUM_API AShootiumAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    AShootiumAIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UShootiumAIPerceptionComponent* ShootiumAIPerceptionComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
};
