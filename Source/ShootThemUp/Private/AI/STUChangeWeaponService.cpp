// Shoot Them Up. All Rights Reserved


#include "AI/STUChangeWeaponService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "ShootThemUp/Components/STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probabiliti > 0 && FMath::FRand() <= Probabiliti)
		{
			WeaponComponent->NextWeapon();

		}
	}



	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}
