// Shoot Them Up. All Rights Reserved


#include "ShootThemUp/Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h" 
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShakeBase.h"


// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
	}
	
}


void USTUHealthComponent::AutoHealing()
{
	SetHealth( Health + HealModifier);
	

	if(FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimeUpdete);
	}
}


void USTUHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	

	if (Damage <= 0 || IsDead() || !GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(TimeUpdete);
	
	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
		
	}
	
	if (AutoHeal && Health < MaxHealth && Health > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeUpdete, this, &USTUHealthComponent::AutoHealing, HealUpdateTime, true, HealDelay);
	}
	
	PlayCameraShake();
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}


bool USTUHealthComponent::TryToAddHealth(int32 HealthAmount)
{
	if (Health == MaxHealth) return false;
	
	SetHealth(Health+HealthAmount);
	return true;
}

void USTUHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;
	
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}