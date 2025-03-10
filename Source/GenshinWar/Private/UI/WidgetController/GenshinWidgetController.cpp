// Copyright 2025 鸿源z。保留所有权利。


#include "UI/WidgetController/GenshinWidgetController.h"
#include "AbilitySystem/Attribute/GenshinAttributeSet.h"

void UGenshinWidgetController::BroadcastInitialValues()
{
	UGenshinAttributeSet* GenshinAttributeSet = Cast<UGenshinAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(GenshinAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GenshinAttributeSet->GetMaxHealth());
	
	OnStaminaChanged.Broadcast(GenshinAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(GenshinAttributeSet->GetMaxStamina());
	
	OnShieldChanged.Broadcast(GenshinAttributeSet->GetShield());
	OnMaxShieldChanged.Broadcast(GenshinAttributeSet->GetMaxShield());
}

void UGenshinWidgetController::BindCallbacksToDependencies()
{
	UGenshinAttributeSet* GenshinAttributeSet = Cast<UGenshinAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnStaminaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetMaxStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxStaminaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetShieldAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnShieldChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GenshinAttributeSet->GetMaxShieldAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxShieldChanged.Broadcast(Data.NewValue);
			}
		);
}
