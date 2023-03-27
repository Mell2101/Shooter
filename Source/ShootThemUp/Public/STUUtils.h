#pragma once

class APawn;

class STUUtils
{
public:
	template<typename T>
	static T* GetSTUPlayerComponent(AActor* Player)
	{
		
		if (!Player) return nullptr;

		const auto Component = Player->GetComponentByClass(T::StaticClass());
		const auto HealthComponent = Cast<T>(Component);

		return HealthComponent;
	}
};