// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootiumCoreTypes.h"
#include "ShootiumBaseWeapon.generated.h"



class USkeletalMeshComponent;

UCLASS()
class SHOOTIUM_API AShootiumBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AShootiumBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload() const; 

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 5000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo;

	virtual void BeginPlay() override;

	virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;

    void LogAmmo();
    
private:
    FAmmoData CurrentAmmo;


};
