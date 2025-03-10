// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "../GenshinAbilitySystemComponent.h"
#include "GenshinAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 属性集
 */
UCLASS()
class GENSHINWAR_API UGenshinAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	//生命值
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Health);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxHealth);

	//体力值
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Stamina);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxStamina);

	//护盾值
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, Shield);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Important")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MaxShield);

	//移动速度
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Move")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UGenshinAttributeSet, MoveSpeed);

	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
