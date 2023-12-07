// Shootium Game. All Rights Reserved.

#include "Components/ShootiumWeaponComponent.h"
#include "Weapon/ShootiumBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/ShootiumEquipFinishedAN.h"
#include "Animations/ShootiumReloadFinishedAN.h"
#include "Animations/AnimUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UShootiumWeaponComponent::UShootiumWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UShootiumWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

    InitAnimations();
    CurrentWeaponIndex = 0;
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
    if (!Character || !GetWorld())
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AShootiumBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon)
            continue;

        Weapon->OnClipEmpty.AddUObject(this, &UShootiumWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponHolsterSocketName);
    }
}

void UShootiumWeaponComponent::AttachWeaponToSocket(AShootiumBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UShootiumWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
        return;
    }

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponHolsterSocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { //
        return Data.WeaponClass == CurrentWeapon->GetClass();                                //
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UShootiumWeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    CurrentWeapon->StartFire();
}

void UShootiumWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void UShootiumWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UShootiumWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
}

void UShootiumWeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UShootiumEquipFinishedAN>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UShootiumWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anom notify is forgotten to set"));
        checkNoEntry();
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadinishedNotify = AnimUtils::FindNotifyByClass<UShootiumReloadFinishedAN>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anom notify is forgotten to set"));
            checkNoEntry();
        }

        ReloadinishedNotify->OnNotified.AddUObject(this, &UShootiumWeaponComponent::OnReloadFinished);
    }
}

void UShootiumWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh())
        return;

    EquipAnimProgress = false;
}

void UShootiumWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh())
        return;

    ReloadAnimProgress = false;
}

bool UShootiumWeaponComponent::CanFire()
{
    return CurrentWeapon && !EquipAnimProgress && !ReloadAnimProgress;
}

bool UShootiumWeaponComponent::CanEquip()
{
    return !EquipAnimProgress && !ReloadAnimProgress;
}

bool UShootiumWeaponComponent::CanReload()
{
    return CurrentWeapon          //
           && !EquipAnimProgress  //
           && !ReloadAnimProgress //
           && CurrentWeapon->CanReload();
}

void UShootiumWeaponComponent::Reload()
{
    ChangeClip();
}

void UShootiumWeaponComponent::OnEmptyClip()
{
    ChangeClip();
}

void UShootiumWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    ReloadAnimProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}