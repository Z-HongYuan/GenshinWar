// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GenshinAbilityTargetActor_Trace.h"
#include "GenshinAbilityTargetActor_LineTrace.generated.h"

UCLASS()
class GENSHINWAR_API AGenshinAbilityTargetActor_LineTrace : public AGenshinAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGenshinAbilityTargetActor_LineTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
