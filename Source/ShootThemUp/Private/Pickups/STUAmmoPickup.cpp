// Shoot Them Up. All Rights Reserved


#include "Pickups/STUAmmoPickup.h"
#include "ShootThemUp/Components/STUHealthComponent.h"
#include "ShootThemUp/Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePikupTo(APawn* Player)
{

    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Player);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Player);
    if (!WeaponComponent) return false;

   return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
