// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumLauncherWeapon.h"
#include "Weapon/ShootiumProjectile.h"

void AShootiumLauncherWeapon::StartFire() 
{
    MakeShot();
}

void AShootiumLauncherWeapon::MakeShot() 
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AShootiumProjectile* Projectile = GetWorld()->SpawnActorDeferred<AShootiumProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->FinishSpawning(SpawnTransform);
    }
}
