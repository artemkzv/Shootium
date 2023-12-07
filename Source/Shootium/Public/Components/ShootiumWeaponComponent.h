// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootiumWeaponComponent.generated.h"

class AShootiumBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AShootiumBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTIUM_API UShootiumWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootiumWeaponComponent();

	void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray < FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "RifleHandSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponHolsterSocketName = "LauncherHolsterSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; 

private:
    UPROPERTY()
    AShootiumBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
    TArray<AShootiumBaseWeapon*> Weapons;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
    bool EquipAnimProgress = false;
    bool ReloadAnimProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AShootiumBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanFire();
    bool CanEquip();
    bool CanReload();

    void OnEmptyClip();
    void ChangeClip();

    template<typename T> 
    T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation) return nullptr;

        const auto NotifyEvents = Animation->Notifies;
        for (auto NotifyEvent : NotifyEvents)
        {
            auto AnimNotify = Cast<T>(NotifyEvent.Notify);
            if (AnimNotify)
            {
                return AnimNotify;
            }
        }
        return nullptr;
    }
};
