// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootiumRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTIUM_API UShootiumRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootiumRespawnComponent();

	void Respawn(int32 RespawnTime);

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();
};