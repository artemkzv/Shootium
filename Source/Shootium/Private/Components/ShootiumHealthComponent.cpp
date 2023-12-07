// Shootium Game. All Rights Reserved.


#include "Components/ShootiumHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

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
        OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
        GetWorld()->GetTimerManager().SetTimer(
            HealTimerHandle, this, &UShootiumHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
}

void UShootiumHealthComponent::HealUpdate() 
{
    SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UShootiumHealthComponent::SetHealth(float NewHealth) 
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}



