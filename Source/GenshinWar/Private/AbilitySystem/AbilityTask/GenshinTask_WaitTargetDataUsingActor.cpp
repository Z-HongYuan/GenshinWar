// Copyright 2025 鸿源z。保留所有权利。


#include "AbilitySystem/AbilityTask/GenshinTask_WaitTargetDataUsingActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Actor/TargetDataActor/GenshinAbilityTargetActor_LineTrace.h"

UGenshinTask_WaitTargetDataUsingActor* UGenshinTask_WaitTargetDataUsingActor::CreateTargetDataUsingActorProxy(
	UGameplayAbility* OwningAbility, FName TaskInstanceName,
	TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* InTargetActor,
	bool bCreateKeyIfNotValidForMorePredicting)
{
	UGenshinTask_WaitTargetDataUsingActor* MyObj = NewAbilityTask<UGenshinTask_WaitTargetDataUsingActor>(OwningAbility, TaskInstanceName);
	MyObj->TargetActor = InTargetActor;
	MyObj->ConfirmationType = ConfirmationType;
	MyObj->bCreateKeyIfNotValidForMorePredicting = bCreateKeyIfNotValidForMorePredicting;
	return MyObj;
}

void UGenshinTask_WaitTargetDataUsingActor::Activate()
{
	// IsPendingKill() == !IsValid(this) This Is True?
	if (!IsValid(this))
	{
		return;
	}
	
	if (Ability && TargetActor)
	{
		InitializeTargetActor();
		RegisterTargetDataCallbacks();
		FinalizeTargetActor();
	}
	else
	{
		EndTask();
	}
}

void UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data,
	FGameplayTag ActivationTag)
{
	check(AbilitySystemComponent.Get());
	
	FGameplayAbilityTargetDataHandle MutableData = Data;
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	/**
	 *  调用 TargetActor 以清理/验证数据。如果返回 false，则拒绝
	 * 复制的目标数据，并将其视为取消。
	 *
	 * 这也可用于带宽优化。OnReplicatedTargetDataReceived 可以执行实际的
	 * 跟踪/检查/任何服务器端并使用该数据。因此，与其让客户端发送该数据
	 * 明确地说，客户端基本上只是发送一个 'confirm'，服务器现在将完成这项工作
	 * 在 OnReplicatedTargetDataReceived 中。
	 */
	if (TargetActor && !TargetActor->OnReplicatedTargetDataReceived(MutableData))
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			Cancelled.Broadcast(MutableData);
		}
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(MutableData);
		}
	}

	if (ConfirmationType != EGameplayTargetingConfirmation::CustomMulti)
	{
		EndTask();
	}
}

void UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReplicatedCancelledCallback()
{
	check(AbilitySystemComponent.Get());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		Cancelled.Broadcast(FGameplayAbilityTargetDataHandle());
	}
	EndTask();
}

void UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& Data)
{
	check(AbilitySystemComponent.Get());
	if (!Ability)
	{
		return;
	}
	
	FScopedPredictionWindow	ScopedPrediction(AbilitySystemComponent.Get(),
		ShouldReplicateDataToServer() && (bCreateKeyIfNotValidForMorePredicting && !AbilitySystemComponent->ScopedPredictionKey.IsValidForMorePrediction()));

	const FGameplayAbilityActorInfo* Info = Ability->GetCurrentActorInfo();
	
	if (IsPredictingClient())
	{
		if (!TargetActor->ShouldProduceTargetDataOnServer)
		{
			FGameplayTag ApplicationTag; // Fixme：这在哪些地方有用？
			AbilitySystemComponent->CallServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), Data, ApplicationTag, AbilitySystemComponent->ScopedPredictionKey);
		}
		else if (ConfirmationType == EGameplayTargetingConfirmation::UserConfirmed)
		{
			// 我们不会发送目标数据，但会发送一条通用的确认消息。
			AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}

	if (ConfirmationType != EGameplayTargetingConfirmation::CustomMulti)
	{
		EndTask();
	}
}

void UGenshinTask_WaitTargetDataUsingActor::OnTargetDataCancelledCallback(const FGameplayAbilityTargetDataHandle& Data)
{
	check(AbilitySystemComponent.Get());
	
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get(), IsPredictingClient());

	if (IsPredictingClient())
	{
		if (!TargetActor->ShouldProduceTargetDataOnServer)
		{
			AbilitySystemComponent->ServerSetReplicatedTargetDataCancelled(GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
		}
		else
		{
			// 我们不会发送目标数据，但会发送一条通用的确认消息。
			AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericCancel, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
		}
	}
	Cancelled.Broadcast(Data);
	EndTask();
}

void UGenshinTask_WaitTargetDataUsingActor::ExternalConfirm(bool bEndTask)
{
	check(AbilitySystemComponent.Get());
	if (TargetActor)
	{
		if (TargetActor->ShouldProduceTargetData())
		{
			TargetActor->ConfirmTargetingAndContinue();
		}
	}
	Super::ExternalConfirm(bEndTask);
}

void UGenshinTask_WaitTargetDataUsingActor::ExternalCancel()
{
	check(AbilitySystemComponent.Get());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		Cancelled.Broadcast(FGameplayAbilityTargetDataHandle());
	}
	Super::ExternalCancel();
}

void UGenshinTask_WaitTargetDataUsingActor::InitializeTargetActor() const
{
	check(TargetActor);
	check(Ability);

	TargetActor->PrimaryPC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	// 如果我们生成了目标 actor，请始终在数据准备就绪时注册回调。
	TargetActor->TargetDataReadyDelegate.AddUObject(const_cast<UGenshinTask_WaitTargetDataUsingActor*>(this), &UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReadyCallback);
	TargetActor->CanceledDelegate.AddUObject(const_cast<UGenshinTask_WaitTargetDataUsingActor*>(this), &UGenshinTask_WaitTargetDataUsingActor::OnTargetDataCancelledCallback);

}

void UGenshinTask_WaitTargetDataUsingActor::FinalizeTargetActor() const
{
	check(TargetActor);
	check(Ability);

	TargetActor->StartTargeting(Ability);

	if (TargetActor->ShouldProduceTargetData())
	{
		/**
		 如果是即时确认，则立即停止定位。
		 请注意，这有点糟糕：我们应该能够在 CDO 上调用 static func 来做到这一点。
		 但是，我们将无法设置 ExposeOnSpawnParameters。
		*/
		if (ConfirmationType == EGameplayTargetingConfirmation::Instant)
		{
			TargetActor->ConfirmTargeting();
		}
		else if (ConfirmationType == EGameplayTargetingConfirmation::UserConfirmed)
		{
			// 绑定到 Cancel/Confirm Delegates（从本地确认或从 repped confirm 调用）
			TargetActor->BindToConfirmCancelInputs();
		}
	}
}

void UGenshinTask_WaitTargetDataUsingActor::RegisterTargetDataCallbacks()
{
	if (!ensure(!IsValid(this) == false))
	{
		return;
	}

	check(Ability);

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	const bool bShouldProduceTargetDataOnServer = TargetActor->ShouldProduceTargetDataOnServer;

	// 如果不是本地控制的（远程客户端的服务器），请查看 TargetData 是否已发送，否则在它到达此处时注册回调。
	if (!bIsLocallyControlled)
	{
		// 如果我们期望客户端发送 TargetData 回调，请注册它们
		if (!bShouldProduceTargetDataOnServer)
		{
			FGameplayAbilitySpecHandle	SpecHandle = GetAbilitySpecHandle();
			FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

			//由于支持 multifire，我们仍然需要 hook 回调
			AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReplicatedCallback);
			AbilitySystemComponent->AbilityTargetDataCancelledDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UGenshinTask_WaitTargetDataUsingActor::OnTargetDataReplicatedCancelledCallback);

			AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);

			SetWaitingOnRemotePlayerData();
		}
	}
}

void UGenshinTask_WaitTargetDataUsingActor::OnDestroy(bool AbilityEnded)
{
	if (TargetActor)
	{
		if (AGenshinAbilityTargetActor_LineTrace* TraceTargetActor = Cast<AGenshinAbilityTargetActor_LineTrace>(TargetActor))
		{
			TraceTargetActor->StopTargeting();
		}
		else
		{
			// TargetActor 没有 StopTargeting 函数
			TargetActor->SetActorTickEnabled(false);

			// 清除添加的回调
			TargetActor->TargetDataReadyDelegate.RemoveAll(this);
			TargetActor->CanceledDelegate.RemoveAll(this);

			AbilitySystemComponent->GenericLocalConfirmCallbacks.RemoveDynamic(TargetActor, &AGameplayAbilityTargetActor::ConfirmTargeting);
			AbilitySystemComponent->GenericLocalCancelCallbacks.RemoveDynamic(TargetActor, &AGameplayAbilityTargetActor::CancelTargeting);
			TargetActor->GenericDelegateBoundASC = nullptr;
		}
	}

	Super::OnDestroy(AbilityEnded);
}

bool UGenshinTask_WaitTargetDataUsingActor::ShouldReplicateDataToServer() const
{
	if (!Ability || !TargetActor)
	{
		return false;
	}

	// Send TargetData to the server（将 TargetData发送到服务器），IFF 我们是客户端，这不是可以在服务器上生成数据的 GameplayTargetActor	
	const FGameplayAbilityActorInfo* Info = Ability->GetCurrentActorInfo();
	if (!Info->IsNetAuthority() && !TargetActor->ShouldProduceTargetDataOnServer)
	{
		return true;
	}

	return false;
}
