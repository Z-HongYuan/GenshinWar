// Copyright 2025 鸿源z。保留所有权利。


#include "UI/GenshinHUD.h"
#include "AbilitySystemGlobals.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AGenshinHUD::AGenshinHUD()
{
	
}

void AGenshinHUD::SetGameplayTagPropertyMap(AActor* ListenInActor)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ListenInActor))
	{
		check(ASC);
		GameplayTagPropertyMap.Initialize(this,ASC);
	}
}

void AGenshinHUD::InitMainWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (MainWidgetClass)
	{
		MainWidget = CreateWidget<UGenshinUserWidget>(GetOwningPlayerController(),MainWidgetClass);

		const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
		MainWidget->SetWidgetController(GetOverlayWeightController(WidgetControllerParams));
		
		GetOverlayWeightController(WidgetControllerParams)->BroadcastInitialValues();
		
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		MainWidget->AddToViewport();
	}
}

UGenshinWidgetController* AGenshinHUD::GetOverlayWeightController(const FWidgetControllerParams& WCParams)
{
	if (WidgetControllerMain==nullptr)
	{
		WidgetControllerMain=NewObject<UGenshinWidgetController>(this,WidgetControllerMainClass);
		WidgetControllerMain->SetWidgetControllerParams(WCParams);
		WidgetControllerMain->BindCallbacksToDependencies();
		return WidgetControllerMain;
	}
	return WidgetControllerMain;
}
