// Shoot Them Up. All Rights Reserved


#include "Pickups/STUHealthPickup.h"
#include "ShootThemUp/Components/STUHealthComponent.h"
#include "STUUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePikupTo(APawn* Player)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Player);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
