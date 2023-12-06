// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootiumWeaponComponent.generated.h"

class AShootiumBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTIUM_API UShootiumWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootiumWeaponComponent();

	void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<AShootiumBaseWeapon>> WeaponClasses;

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

	int32 CurrentWeaponIndex = 0;
    bool EquipAnimProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AShootiumBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);

    bool CanFire();
    bool CanEquip();
};
