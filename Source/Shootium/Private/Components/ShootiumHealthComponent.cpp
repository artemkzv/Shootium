// Shootium Game. All Rights Reserved.


#include "Components/ShootiumHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UShootiumHealthComponent::UShootiumHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}

void UShootiumHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShootiumHealthComponent::OnTakeAnyDamage);
	}
}

void UShootiumHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

	if (IsDead())
	{
        OnDeath.Broadcast();
	}
}



