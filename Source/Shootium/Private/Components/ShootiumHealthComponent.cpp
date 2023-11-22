// Shootium Game. All Rights Reserved.


#include "Components/ShootiumHealthComponent.h"

UShootiumHealthComponent::UShootiumHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}



void UShootiumHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}



