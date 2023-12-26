// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootiumPlayerController.generated.h"

class UShootiumRespawnComponent;

UCLASS()
class SHOOTIUM_API AShootiumPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AShootiumPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UShootiumRespawnComponent* RespawnComponent;
};
