// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GenshinInputDataAsset.generated.h"

//原生Action+Tag
USTRUCT(BlueprintType)
struct FGenshinInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 用于绑定Tag到Action的数据资产
 */
UCLASS()
class GENSHINWAR_API UGenshinInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//通过Tag获取 Action
	const UInputAction* GetInputActionForTag(const FGameplayTag& InputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGenshinInputAction> AbilityInputActions;
};
