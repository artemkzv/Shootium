// Shootium Game. All Rights Reserved.


#include "Player/ShootiumBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AShootiumBaseCharacter::AShootiumBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());

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
}

void AShootiumBaseCharacter::MoveForward(float Amount) 
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AShootiumBaseCharacter::MoveRight(float Amount) 
{
    AddMovementInput(GetActorRightVector(), Amount);
}

