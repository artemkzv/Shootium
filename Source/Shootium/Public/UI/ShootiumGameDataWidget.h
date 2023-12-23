// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootiumGameDataWidget.generated.h"

class AShootiumGameModeBase;
class AShootiumPlayerState;

UCLASS()
class SHOOTIUM_API UShootiumGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
    AShootiumGameModeBase* GetShootiumGameMode() const;
    AShootiumPlayerState* GetShootiumPlayerState() const;
};
