// Copyright 2025 鸿源z。保留所有权利。


#include "Input/Data/GenshinInputDataAsset.h"

const UInputAction* UGenshinInputDataAsset::GetInputActionForTag(const FGameplayTag& InputTag) const
{
	for (FGenshinInputAction Action : AbilityInputActions)
	{
		if (Action.InputTag==InputTag && Action.InputAction)
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
