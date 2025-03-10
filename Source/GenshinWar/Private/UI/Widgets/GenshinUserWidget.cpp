// Copyright 2025 鸿源z。保留所有权利。


#include "UI/Widgets/GenshinUserWidget.h"
#include "AbilitySystemGlobals.h"

void UGenshinUserWidget::SetGameplayTagPropertyMap(AActor* ListenInActor)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ListenInActor))
	{
		check(ASC);
		GameplayTagPropertyMap.Initialize(this,ASC);
	}
}

void UGenshinUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController=InWidgetController;
	WidgetControllerSet();
}
