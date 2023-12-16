// Shootium Game. All Rights Reserved.


#include "Weapon/Components/ShootiumWeaponFXComponent.h"
//#include "AutomationBlueprintFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"

UShootiumWeaponFXComponent::UShootiumWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShootiumWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto Effect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}