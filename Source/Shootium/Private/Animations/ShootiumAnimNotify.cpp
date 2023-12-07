// Shootium Game. All Rights Reserved.


#include "Animations/ShootiumAnimNotify.h"

void UShootiumAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}