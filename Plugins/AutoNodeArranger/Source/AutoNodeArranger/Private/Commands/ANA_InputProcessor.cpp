// Copyright 2022 bstt, Inc. All Rights Reserved.

#include "ANA_InputProcessor.h"
#include "../Helpers/ANA_CommandHelper.h"
#include "../Arrangement/ANA_Manager.h"
#include "../Config/ANA_ProjectConfig.h"
#include "../Debug/Debug.h"
#include "Input/Events.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Layout/WidgetPath.h"
#include "Widgets/Notifications/SNotificationList.h"

TSharedPtr<ANA_InputProcessor> ANA_InputProcessor::instance = nullptr;

void ANA_InputProcessor::RegisterProcessor()
{
	instance = MakeShareable(new ANA_InputProcessor());
	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().RegisterInputPreProcessor(instance);
}

void ANA_InputProcessor::UnregisterProcessor()
{
	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().UnregisterInputPreProcessor(instance);
	instance.Reset();
}

void ANA_InputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
	ANA_Manager::instance.TickImp(DeltaTime);

	AutoRegisterNodes(DeltaTime);
}

void ANA_InputProcessor::AutoRegisterNodes(const float DeltaTime)
{
	if (!currentWeakSGraphPanel.IsValid())
		return;
	SGraphPanel* graphPanel = currentWeakSGraphPanel.Pin().Get();

	updateNodeSizeTime -= DeltaTime;
	if (updateNodeSizeTime < 0.f)
	{
		for (auto graphNode : graphPanel->GetGraphObj()->Nodes)
		{
			FVector2D pos = FVector2D(graphNode->NodePosX, graphNode->NodePosY);
			FVector2D size = FVector2D(graphNode->NodeWidth, graphNode->NodeHeight);
			FSlateRect graphRect = FSlateRect::FromPointAndExtent(pos, size);
			if (graphPanel->IsRectVisible(graphRect.GetTopLeft(), graphRect.GetBottomRight()))
				UANA_ProjectConfig::RegisterNode(currentNamedGuid, graphNode, graphPanel);
		}
		UANA_ProjectConfig::Get()->SaveConfig();
		updateNodeSizeTime = 1.f; // auto registering nodes each second
	}
}
