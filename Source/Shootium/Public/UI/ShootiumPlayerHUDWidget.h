// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootiumPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTIUM_API UShootiumPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
};
