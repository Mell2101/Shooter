// Shoot Them Up. All Rights Reserved


#include "ShootThemUp/Components/STUCharacterMovementComponent.h"
#include "STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	ASTUBaseCharacter* player = Cast<ASTUBaseCharacter>(GetPawnOwner());
	return player && player->IsRunning() ? MaxSpeed*RunModifier : MaxSpeed;
}
