// Shoot Them Up. All Rights Reserved


#include "Animation/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
