// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShootiumBaseCharacter.h"
#include "ShootiumAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTIUM_API AShootiumAICharacter : public AShootiumBaseCharacter
{
	GENERATED_BODY()
	
public:
    AShootiumAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;
};
