// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ShootiumAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FNotifiedSignature, USkeletalMeshComponent*);

UCLASS()
class SHOOTIUM_API UShootiumAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    FNotifiedSignature OnNotified;
};
