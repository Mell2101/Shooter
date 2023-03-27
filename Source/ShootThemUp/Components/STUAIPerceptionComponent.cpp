// Shoot Them Up. All Rights Reserved


#include "ShootThemUp/Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "ShootThemUp/Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercievActors;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievActors);
	if (PercievActors.Num() == 0) return nullptr;
	
	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercActor : PercievActors)
	{
		const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PercActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PercActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercActor;
			}
		}
	}

	return BestPawn;
}
