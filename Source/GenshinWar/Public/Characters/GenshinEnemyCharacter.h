// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "Characters/GenshinCharacterBase.h"
#include "GenshinEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINWAR_API AGenshinEnemyCharacter : public AGenshinCharacterBase
{
	GENERATED_BODY()
public:
	AGenshinEnemyCharacter(const class FObjectInitializer& ObjectInitializer);

	
protected:
	virtual void BeginPlay() override;

	
	virtual void InitAbilitySystemComponent() override;
};
