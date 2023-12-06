// Shootium Game. All Rights Reserved.


#include "Components/ShootiumWeaponComponent.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/ShootiumEquipFinishedAN.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UShootiumWeaponComponent::UShootiumWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UShootiumWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
	SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UShootiumWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}


void UShootiumWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<AShootiumBaseWeapon>(WeaponClass);
        if (!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponHolsterSocketName);
    }
}

void UShootiumWeaponComponent::AttachWeaponToSocket(AShootiumBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}


void UShootiumWeaponComponent::EquipWeapon(int32 WeaponIndex) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponHolsterSocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UShootiumWeaponComponent::StartFire() 
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UShootiumWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UShootiumWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UShootiumWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}

void UShootiumWeaponComponent::InitAnimations() 
{
    if (!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<UShootiumEquipFinishedAN>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &UShootiumWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void UShootiumWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh()) return;
 
        EquipAnimProgress = false;

}

bool UShootiumWeaponComponent::CanFire()
{
        return CurrentWeapon && !EquipAnimProgress;
}

bool UShootiumWeaponComponent::CanEquip()
{
    return !EquipAnimProgress;
}
