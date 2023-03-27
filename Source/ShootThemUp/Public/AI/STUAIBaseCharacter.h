// Shoot Them Up. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseCharacter.h"
#include "STUAIBaseCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API ASTUAIBaseCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;
protected:

	virtual void OnDeath() override;
	
};
