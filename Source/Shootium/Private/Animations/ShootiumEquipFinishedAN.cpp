// Shootium Game. All Rights Reserved.


#include "Animations/ShootiumEquipFinishedAN.h"

void UShootiumEquipFinishedAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
