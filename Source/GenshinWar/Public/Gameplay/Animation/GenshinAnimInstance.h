// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "GenshinAnimInstance.generated.h"

/**
 * 带有Tag绑定变量的动画实例
 */
UCLASS()
class GENSHINWAR_API UGenshinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|GameplayTags")
	void SetGameplayTagPropertyMap(AActor* ListenInActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
