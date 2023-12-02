// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootiumGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTIUM_API AShootiumGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
