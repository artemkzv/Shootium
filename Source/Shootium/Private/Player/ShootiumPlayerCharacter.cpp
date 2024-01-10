// Shootium Game. All Rights Reserved.


#include "Player/ShootiumPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ShootiumWeaponComponent.h"

AShootiumPlayerCharacter::AShootiumPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShootiumPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AShootiumPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AShootiumPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AShootiumPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AShootiumPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShootiumPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShootiumPlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AShootiumPlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UShootiumWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UShootiumWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UShootiumWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UShootiumWeaponComponent::Reload);
}

void AShootiumPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AShootiumPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AShootiumPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AShootiumPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

bool AShootiumPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AShootiumPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    // PlayAnimMontage(DeathAnimMontage);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}