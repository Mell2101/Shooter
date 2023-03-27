// Shoot Them Up. All Rights Reserved


#include "AI/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "ShootThemUp/Components/STUAIPerceptionComponent.h"


USTUFindEnemyService::USTUFindEnemyService()
{
	NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (BlackBoard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PercepComp = STUUtils::GetSTUPlayerComponent<USTUAIPerceptionComponent>(Controller);
		if (PercepComp)
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PercepComp->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
