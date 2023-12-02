// Shootium Game. All Rights Reserved.


#include "Player/ShootiumBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ShootCharacterMovementComponent.h"
#include "Components/ShootiumHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Weapon/ShootiumBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
AShootiumBaseCharacter::AShootiumBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UShootCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UShootiumHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AShootiumBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AShootiumBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AShootiumBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AShootiumBaseCharacter::OnGroundLanded);

    SpawnWeapon();
	
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
    check(PlayerInputComponent);

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

void AShootiumBaseCharacter::OnDeath() 
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void AShootiumBaseCharacter::OnHealthChanged(float Health) 
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AShootiumBaseCharacter::OnGroundLanded(const FHitResult& Hit) 
{
    if (ApplyLandedDamage)
    {
        const auto FallVelocityZ = -GetVelocity().Z;
        UE_LOG(LogBaseCharacter, Display, TEXT("On landed: %f"), FallVelocityZ);

        if (FallVelocityZ < LandedDamageVelocity.X) return;

        const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
        UE_LOG(LogBaseCharacter, Display, TEXT("FinalDamage: %f"), FinalDamage);
        TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
    }
    
}

void AShootiumBaseCharacter::SpawnWeapon() 
{
    if (!GetWorld()) return;

    const auto Weapon = GetWorld()->SpawnActor<AShootiumBaseWeapon>(WeaponClass);
    if (Weapon)
    {
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
        Weapon->AttachToComponent(GetMesh(), AttachmentRules, "RifleHandSocket");
    }
}



