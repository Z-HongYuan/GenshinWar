// Copyright 2022 bstt, Inc. All Rights Reserved.

#pragma once

#include "Framework/Application/IInputProcessor.h"
#include "../Config/NamedGuid.h"
#include "SGraphPin.h"

/**
 *
 */
class ANA_InputProcessor : public IInputProcessor
{
	ANA_InputProcessor() = default;

public:
	static void RegisterProcessor();
	static void UnregisterProcessor();

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

private:
	// called on tick
	void AutoRegisterNodes(const float DeltaTime);

	static TSharedPtr<ANA_InputProcessor> instance;

	TWeakPtr<SGraphPanel> currentWeakSGraphPanel = nullptr;
	FNamedGuid currentNamedGuid;
	UEdGraphPin* currentGraphPin = nullptr;

	// used in AutoRegisterNodes
	int countdownTickCount = -1;
	float updateNodeSizeTime = 0.f;

	// used in UpdatePinLinkedTo
	TArray<UEdGraphPin*> oldLinkedTo;
	bool bControlDown = false;

	// used in CheckDeselection
	bool oldIsDeselected = true;
};
