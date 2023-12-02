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

	virtual void Fire();

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

	void MakeShot();
};
