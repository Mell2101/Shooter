// Shoot Them Up. All Rights Reserved


#include "AI/STUHealthPercentBTDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "ShootThemUp/Components/STUHealthComponent.h"

USTUHealthPercentBTDecorator::USTUHealthPercentBTDecorator()
{
	NodeName = "Health Percent";
}

bool USTUHealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
