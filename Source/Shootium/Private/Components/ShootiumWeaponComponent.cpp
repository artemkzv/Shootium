// Shootium Game. All Rights Reserved.


#include "Components/ShootiumWeaponComponent.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "GameFramework/Character.h"

UShootiumWeaponComponent::UShootiumWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UShootiumWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UShootiumWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<AShootiumBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}

void UShootiumWeaponComponent::Fire() 
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}

