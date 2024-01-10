// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShootiumBaseCharacter.h"
#include "ShootiumPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTIUM_API AShootiumPlayerCharacter : public AShootiumBaseCharacter
{
	GENERATED_BODY()
	
public:
    AShootiumPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    virtual void OnDeath() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual bool IsRunning() const override;

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();
};
