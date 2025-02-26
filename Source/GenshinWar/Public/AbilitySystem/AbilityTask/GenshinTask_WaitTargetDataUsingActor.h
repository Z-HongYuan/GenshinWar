// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GenshinTask_WaitTargetDataUsingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGWaitTargetDataUsingActorDelegate, const FGameplayAbilityTargetDataHandle&, Data);

/**
 * 这个是用于蓝图使用的TargetActorData委托
 * 异步任务节点
 * 用传入的Actor来获取由Actor生成的目标数据
 */
UCLASS()
class GENSHINWAR_API UGenshinTask_WaitTargetDataUsingActor : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FGWaitTargetDataUsingActorDelegate ValidData;

	UPROPERTY(BlueprintAssignable)
	FGWaitTargetDataUsingActorDelegate Cancelled;

	
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (
		DisplayName="GenshinTask_WaitTargetDataUsingActor",
		HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "TRUE",
		HideSpawnParms = "Instigator"))
	static UGenshinTask_WaitTargetDataUsingActor* CreateTargetDataUsingActorProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType,
		AGameplayAbilityTargetActor* InTargetActor,
		bool bCreateKeyIfNotValidForMorePredicting = false
	);
	
	virtual void Activate() override;
	
	UFUNCTION()
	virtual void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);

	UFUNCTION()
	virtual void OnTargetDataReplicatedCancelledCallback();

	UFUNCTION()
	virtual void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	virtual void OnTargetDataCancelledCallback(const FGameplayAbilityTargetDataHandle& Data);

	// 当要求功能从外部节点确认时调用。这意味着什么取决于单个任务。默认情况下，这除了在 bEndTask 为 true 时结束之外，不执行任何作。
	virtual void ExternalConfirm(bool bEndTask) override;

	// 当要求从外部节点取消功能时调用。这意味着什么取决于单个任务。默认情况下，这只会结束任务。
	virtual void ExternalCancel() override;

protected:
	UPROPERTY()
	AGameplayAbilityTargetActor* TargetActor;
	
	bool bCreateKeyIfNotValidForMorePredicting;

	TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType;
	
	FDelegateHandle OnTargetDataReplicatedCallbackDelegateHandle;

	virtual void InitializeTargetActor() const;
	virtual void FinalizeTargetActor() const;

	virtual void RegisterTargetDataCallbacks();

	virtual void OnDestroy(bool AbilityEnded) override;

	virtual bool ShouldReplicateDataToServer() const;
};
