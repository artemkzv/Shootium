// Shootium Game. All Rights Reserved.


#include "Components/ShootiumHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "ShootiumGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UShootiumHealthComponent::UShootiumHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}



void UShootiumHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShootiumHealthComponent::OnTakeAnyDamage);
	}
}

void UShootiumHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
        Killed(InstigatedBy);
        OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
        GetWorld()->GetTimerManager().SetTimer(
            HealTimerHandle, this, &UShootiumHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
    PlayCameraShake();

}

void UShootiumHealthComponent::HealUpdate() 
{
    SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UShootiumHealthComponent::SetHealth(float NewHealth) 
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}


bool UShootiumHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull())
        return false;

	SetHealth(Health + HealthAmount);
    return true;
}

bool UShootiumHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UShootiumHealthComponent::PlayCameraShake() 
{
    if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UShootiumHealthComponent::Killed(AController* KillerController) 
{
    if (!GetWorld())
        return;

    const auto GameMode = Cast<AShootiumGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}
