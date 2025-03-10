// Copyright 2025 鸿源z。保留所有权利。


#include "AbilitySystem/Attribute/GenshinAttributeSet.h"
#include "GameplayEffectExtension.h"

void UGenshinAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute==GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute==GetStaminaAttribute())
	{
		NewValue=FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
	if (Attribute==GetShieldAttribute())
	{
		NewValue=FMath::Clamp(NewValue, 0.0f, GetMaxShield());
	}
	
}

void UGenshinAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute==GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute==GetShieldAttribute())
	{
		SetShield(FMath::Clamp(GetShield(), 0.0f, GetMaxShield()));
	}
}
