// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootiumCoreTypes.h"
#include "ShootiumWeaponComponent.generated.h"

class AShootiumBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTIUM_API UShootiumWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShootiumWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<AShootiumBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<AShootiumBaseWeapon> WeaponType);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "RifleHandSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponHolsterSocketName = "LauncherHolsterSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    AShootiumBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AShootiumBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire();
    bool CanEquip();
    void EquipWeapon(int32 WeaponIndex);

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimProgress = false;
    bool ReloadAnimProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AShootiumBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanReload();

    void OnEmptyClip(AShootiumBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
