// Shootium Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootiumCoreTypes.h"
#include "ShootiumWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTIUM_API UShootiumWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootiumWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    // TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
