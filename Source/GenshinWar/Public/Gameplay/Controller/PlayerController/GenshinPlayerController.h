// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "AbilitySystem/GenshinAbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "Input/Data/GenshinInputDataAsset.h"
#include "GenshinPlayerController.generated.h"

class UInputMappingContext;

/**
 * 绑定初始的移动/视角输入
 * 绑定了ASC的触发函数
 */
UCLASS()
class GENSHINWAR_API AGenshinPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AGenshinPlayerController();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float LeftRightRate = 0.75;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float UpDownRate = 0.75;
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
private:
	// Input
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LookAction;
	
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UGenshinInputDataAsset> InputDataAsset;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<UGenshinAbilitySystemComponent> GenshinAbilitySystemComponent;
	UGenshinAbilitySystemComponent* GetASC();
};
