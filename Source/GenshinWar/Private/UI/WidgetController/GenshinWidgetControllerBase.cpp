// Copyright 2025 鸿源z。保留所有权利。


#include "UI/WidgetController/GenshinWidgetControllerBase.h"

void UGenshinWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	AttributeSet=WCParams.AttributeSet;
	AbilitySystemComponent=WCParams.AbilitySystemComponent;
	PlayerController=WCParams.PlayerController;
	PlayerState=WCParams.PlayerState;
}

void UGenshinWidgetControllerBase::BroadcastInitialValues()
{
}

void UGenshinWidgetControllerBase::BindCallbacksToDependencies()
{
}
