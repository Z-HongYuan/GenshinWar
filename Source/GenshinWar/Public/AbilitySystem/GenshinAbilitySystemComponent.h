// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GenshinAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINWAR_API UGenshinAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//从输入调用触发技能的函数
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
};
