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

	void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<AShootiumBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "RifleHandSocket";

	virtual void BeginPlay() override;

private:
    UPROPERTY()
    AShootiumBaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
