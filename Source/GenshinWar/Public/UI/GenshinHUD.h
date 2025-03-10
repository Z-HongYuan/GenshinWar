// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/HUD.h"
#include "WidgetController/GenshinWidgetController.h"
#include "Widgets/GenshinUserWidget.h"
#include "GenshinHUD.generated.h"

/**
 * HUD
 */
UCLASS()
class GENSHINWAR_API AGenshinHUD : public AHUD
{
	GENERATED_BODY()
public:
	AGenshinHUD();
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|GameplayTags")
	void SetGameplayTagPropertyMap(AActor* ListenInActor);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|UI")
	void InitMainWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UGenshinWidgetController* GetOverlayWeightController(const FWidgetControllerParams& WCParams);

protected:
	//同步Tag 变量
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem|GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

private:
	UPROPERTY()
	TObjectPtr<UGenshinUserWidget> MainWidget;
	
	UPROPERTY(EditAnywhere, Category = "AbilitySystem|UI")
	TSubclassOf<UGenshinUserWidget> MainWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UGenshinWidgetController> WidgetControllerMain;
	
	UPROPERTY(EditAnywhere, Category = "AbilitySystem|UI")
	TSubclassOf<UGenshinWidgetController> WidgetControllerMainClass;
};
