// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShootiumWeaponComponent.h"
#include "ShootiumAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTIUM_API UShootiumAIWeaponComponent : public UShootiumWeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
