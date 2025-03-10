// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GenshinMovementComponent.generated.h"

/**
 * 覆写了GetSpeed,用于绑定角色上的移动速度属性
 */
UCLASS()
class GENSHINWAR_API UGenshinMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UGenshinMovementComponent();

	
	virtual float GetMaxSpeed() const override;
};
