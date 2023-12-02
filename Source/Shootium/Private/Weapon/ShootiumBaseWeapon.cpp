// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

AShootiumBaseWeapon::AShootiumBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);

}

void AShootiumBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


