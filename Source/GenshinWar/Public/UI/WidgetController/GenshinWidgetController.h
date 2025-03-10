// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/GenshinWidgetControllerBase.h"
#include "GenshinWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature,float,NewValue);
/**
 * WidgetController
 * 用于提供各种信息到UI,比如文本,Icon等信息
 */
UCLASS(BlueprintType,Blueprintable)
class GENSHINWAR_API UGenshinWidgetController : public UGenshinWidgetControllerBase
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnMaxStaminaChanged;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnShieldChanged;

	UPROPERTY(BlueprintAssignable,Category="UI|Attributes")
	FOnAttributeChangeSignature OnMaxShieldChanged;
	
};
