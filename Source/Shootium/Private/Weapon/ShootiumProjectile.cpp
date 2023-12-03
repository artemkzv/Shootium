// Shootium Game. All Rights Reserved.


#include "Weapon/ShootiumProjectile.h"
#include "Components/SphereComponent.h"

AShootiumProjectile::AShootiumProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);
}

void AShootiumProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



