// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootiumBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTIUM_API AShootiumBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AShootiumBaseWeapon();

	virtual void StartFire();
    virtual void StopFire();

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float TimeBetweenShot = 0.1f;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

	virtual void BeginPlay() override;

	void MakeShot();

	APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(const FHitResult& HitResult);

private:
    FTimerHandle ShotTimerHandle;

};
