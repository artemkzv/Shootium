// Shootium Game. All Rights Reserved.


#include "Pickups/ShootiumBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AShootiumBasePickup::AShootiumBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);

}

void AShootiumBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}


void AShootiumBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootiumBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
    Destroy();
}
