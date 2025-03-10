// Copyright 2025 鸿源z。保留所有权利。


#include "Component/GenshinMovementComponent.h"
#include "Characters/GenshinCharacterBase.h"

UGenshinMovementComponent::UGenshinMovementComponent()
{
}

float UGenshinMovementComponent::GetMaxSpeed() const
{
	AGenshinCharacterBase* Owner = Cast<AGenshinCharacterBase>(GetOwner());
	if (!Owner)
	{
		return Super::GetMaxSpeed();
	}
	
	return Owner->GetAttributeSet()->GetMoveSpeed();
}
