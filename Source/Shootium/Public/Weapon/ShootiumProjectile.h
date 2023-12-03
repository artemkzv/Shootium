// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootiumProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTIUM_API AShootiumProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AShootiumProjectile();

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;



};
