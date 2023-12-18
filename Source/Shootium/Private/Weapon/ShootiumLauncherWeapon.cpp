// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumLauncherWeapon.h"
#include "Weapon/ShootiumProjectile.h"
#include "DrawDebugHelpers.h"

void AShootiumLauncherWeapon::StartFire() 
{
    MakeShot();
}

void AShootiumLauncherWeapon::MakeShot() 
{
    if (!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AShootiumProjectile* Projectile = GetWorld()->SpawnActorDeferred<AShootiumProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();

    SpawnMuzzleFX();
}
