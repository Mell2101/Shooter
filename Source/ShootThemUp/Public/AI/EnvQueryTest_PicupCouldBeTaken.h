// Shoot Them Up. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PicupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PicupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
public:

	UEnvQueryTest_PicupCouldBeTaken(const FObjectInitializer& ObjectInitialize);


	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
