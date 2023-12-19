#pragma once

class ShootiumUtils
{
public:
	template <typename T> 
	static T* GetShootiumPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};