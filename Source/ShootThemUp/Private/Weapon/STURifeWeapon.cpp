// Shoot Them Up. All Rights Reserved


#include "Weapon/STURifeWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/VFX/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTURifeWeapon::ASTURifeWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifeWeapon::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifeWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASTURifeWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	SetMuzzleFXVisibility(false);
}

void ASTURifeWeapon::BeginPlay()
{
	Super::BeginPlay();


	check(WeaponFXComponent);
}

void ASTURifeWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;

	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);

		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMazzleWorldLocation(), TraceEnd);

	DecreaseAmmo();
}

bool ASTURifeWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	TraceStart = ViewLocation;
	const FVector ShootDiraction = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDiraction * TraceMaxDistance;
	return true;
}

void ASTURifeWeapon::MakeDamage(FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ASTURifeWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMazzleFX();
	}
	SetMuzzleFXVisibility(true);

}

void ASTURifeWeapon::SetMuzzleFXVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}

void ASTURifeWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}
