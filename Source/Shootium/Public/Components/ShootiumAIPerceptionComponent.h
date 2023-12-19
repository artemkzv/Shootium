// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShootiumAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTIUM_API UShootiumAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
    AActor* GetClosestEnemy() const;
};
