// Copyright 2022 bstt, Inc. All Rights Reserved.

#pragma once

enum CompletedActionType
{
	NONE,
	AUTO_ARRANGE_REMOVED
};

/**
 * 
 */
class ANA_ReleaseNotifier
{
	ANA_ReleaseNotifier() = delete;
public:
	static void RegisterCheckVersion();
	static void CheckVersion();
	static void ShowNotification(CompletedActionType completedActionType_);

private:
	static void ShowAutoArrangeRemovedNotification();
	static void ShowNoneNotification();

	static TWeakPtr<SNotificationItem> releaseNotifPtr;
	static CompletedActionType completeActionType;
};
