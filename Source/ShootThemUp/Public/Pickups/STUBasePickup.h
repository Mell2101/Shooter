// Shoot Them Up. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;

private:
	virtual bool GivePikupTo(APawn* Player);

	FTimerHandle RespanwTimerHandel;

	float RotationYaw = 0.0f;

	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();


};
