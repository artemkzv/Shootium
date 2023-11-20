// Shootium Game. All Rights Reserved.


#include "Components/ShootCharacterMovementComponent.h"
#include "Player/ShootiumBaseCharacter.h"

float UShootCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AShootiumBaseCharacter* Player = Cast<AShootiumBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}
