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

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;

};
