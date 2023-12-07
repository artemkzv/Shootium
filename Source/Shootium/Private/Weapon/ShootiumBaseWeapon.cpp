// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AShootiumBaseWeapon::AShootiumBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);

}

void AShootiumBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
}


void AShootiumBaseWeapon::StartFire() 
{

}

void AShootiumBaseWeapon::StopFire()
{

}

void AShootiumBaseWeapon::MakeShot() 
{

}


APlayerController* AShootiumBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}


bool AShootiumBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;


    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector AShootiumBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AShootiumBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AShootiumBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AShootiumBaseWeapon::DecreaseAmmo() 
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty"));
        return;
    }

    CurrentAmmo.Bullets--;
    LogAmmo();

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast();
    }
}

bool AShootiumBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AShootiumBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void AShootiumBaseWeapon::ChangeClip() 
{

    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(LogBaseWeapon, Display, TEXT(" --------- CHANGE CLIP --------- "));
}

bool AShootiumBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void AShootiumBaseWeapon::LogAmmo() 
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}


