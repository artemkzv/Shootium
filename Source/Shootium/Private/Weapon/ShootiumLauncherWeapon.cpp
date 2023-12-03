// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumLauncherWeapon.h"
#include "Weapon/ShootiumProjectile.h"
#include "Kismet/GameplayStatics.h"

void AShootiumLauncherWeapon::StartFire() 
{
    MakeShot();
}

void AShootiumLauncherWeapon::MakeShot() 
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    // set projectiles params

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
