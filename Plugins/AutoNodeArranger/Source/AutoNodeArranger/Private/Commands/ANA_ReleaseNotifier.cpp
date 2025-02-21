// Copyright 2022 bstt, Inc. All Rights Reserved.

#include "ANA_ReleaseNotifier.h"
#include "../Helpers/ANA_CacheHelper.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "../Debug/Log.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Debug/Debug.h"

#define ANA_NEW_RELEASE_VERSION 417

TWeakPtr<SNotificationItem> ANA_ReleaseNotifier::releaseNotifPtr;
CompletedActionType ANA_ReleaseNotifier::completeActionType = CompletedActionType::NONE;

void ANA_ReleaseNotifier::RegisterCheckVersion()
{
	static FDelegateHandle onAssetEditorOpenedHandle;

	if (UAssetEditorSubsystem* assetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		onAssetEditorOpenedHandle = assetEditorSubsystem->OnAssetEditorOpened().AddLambda(
			[assetEditorSubsystem](UObject* Object)
			{
				ANA_ReleaseNotifier::CheckVersion();
				assetEditorSubsystem->OnAssetEditorOpened().Remove(onAssetEditorOpenedHandle);
			});
}

void ANA_ReleaseNotifier::CheckVersion()
{
	FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();

	if (cacheData.version >= ANA_NEW_RELEASE_VERSION)
		return;
	if (cacheData.laterTime >= FDateTime::UtcNow())
		return;
	if (FDateTime::UtcNow() > FDateTime(2024, 05, 01) + ETimespan::TicksPerDay * 31) // 31 days after the May 1st 2024
		return;
	ShowNotification(CompletedActionType::AUTO_ARRANGE_REMOVED);
}

void ANA_ReleaseNotifier::ShowNotification(CompletedActionType completeActionType_)
{
	completeActionType = completeActionType_;

	switch (completeActionType)
	{
	case AUTO_ARRANGE_REMOVED:
		ShowAutoArrangeRemovedNotification();
		break;
	case NONE:
		ShowNoneNotification();
		break;
	default:
		break;
	}
}

void ANA_ReleaseNotifier::ShowAutoArrangeRemovedNotification()
{
	if (releaseNotifPtr.IsValid())
		return;
	FString message = FString("Auto Node Arranger Info");
	FString subText = FString("For your information,\n"
		"Auto Arrange feature has been removed."
	);

	FNotificationInfo releaseNotif(FText::FromString(message));
	releaseNotif.SubText = FText::FromString(subText);
	releaseNotif.FadeOutDuration = 0.2f;
	releaseNotif.bFireAndForget = false;

	releaseNotif.ButtonDetails.Add(FNotificationButtonInfo(FText::FromString("Ok"),
		FText::FromString("Ok"),
		FSimpleDelegate::CreateLambda([]() {
		releaseNotifPtr.Pin()->SetFadeOutDuration(0.f);
		releaseNotifPtr.Pin()->Fadeout();
		releaseNotifPtr = nullptr;
		// update cache version
		FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();
		cacheData.version = ANA_NEW_RELEASE_VERSION;
		ANA_CacheHelper::SetCacheData(cacheData);
	}),
		SNotificationItem::ECompletionState::CS_None));

	releaseNotifPtr = FSlateNotificationManager::Get().AddNotification(releaseNotif);

	UE_LOG(LogAutoNodeArranger, Log, TEXT("%s\n%s"), *message, *subText);
}

void ANA_ReleaseNotifier::ShowNoneNotification()
{
	// update cache version
	FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();
	cacheData.version = ANA_NEW_RELEASE_VERSION;
	ANA_CacheHelper::SetCacheData(cacheData);
}
