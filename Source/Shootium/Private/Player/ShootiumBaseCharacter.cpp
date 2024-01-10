// Shootium Game. All Rights Reserved.


#include "Player/ShootiumBaseCharacter.h"

#include "Components/ShootCharacterMovementComponent.h"
#include "Components/ShootiumHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ShootiumWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
AShootiumBaseCharacter::AShootiumBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UShootCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UShootiumHealthComponent>("HealthComponent");

    // HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    // HealthTextComponent->SetupAttachment(GetRootComponent());
    // HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<UShootiumWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AShootiumBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    // check(HealthTextComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AShootiumBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AShootiumBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AShootiumBaseCharacter::OnGroundLanded);
	
}

// Called every frame
void AShootiumBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShootiumBaseCharacter::IsRunning() const
{
    return false;
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

    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void AShootiumBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    // HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
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

void AShootiumBaseCharacter::SetPlayerColor(const FLinearColor& Color) 
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}