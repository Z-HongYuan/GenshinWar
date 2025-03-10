// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "GenshinUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINWAR_API UGenshinUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|GameplayTags")
	void SetGameplayTagPropertyMap(AActor* ListenInActor);
	
	UPROPERTY(BlueprintReadOnly,Category="Widget|WidgetController")
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable,Category="Widget|WidgetController")
	void SetWidgetController(UObject* InWidgetController);
	
protected:
	//同步Tag 变量
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
	
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
