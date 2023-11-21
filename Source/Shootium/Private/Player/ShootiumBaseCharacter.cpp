// Shootium Game. All Rights Reserved.


#include "Player/ShootiumBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ShootCharacterMovementComponent.h"

// Sets default values
AShootiumBaseCharacter::AShootiumBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UShootCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void AShootiumBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootiumBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootiumBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShootiumBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AShootiumBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AShootiumBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AShootiumBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AShootiumBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AShootiumBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AShootiumBaseCharacter::OnStopRunning);
}

void AShootiumBaseCharacter::MoveForward(float Amount) 
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AShootiumBaseCharacter::MoveRight(float Amount) 
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AShootiumBaseCharacter::OnStartRunning() 
{
    WantsToRun = true;
}

void AShootiumBaseCharacter::OnStopRunning() 
{
    WantsToRun = false;
}

bool AShootiumBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AShootiumBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}




