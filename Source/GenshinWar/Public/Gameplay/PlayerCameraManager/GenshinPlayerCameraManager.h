// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "GenshinPlayerCameraManager.generated.h"

/**
 * TODO
 * 迁移蓝图到C++,优化代码
 */
UCLASS()
class GENSHINWAR_API AGenshinPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;
	void CalculateCameraParameters(AActor* CameraTarget, FVector& NewCameraLocation, FRotator& NewCameraRotation, float& NewCameraFOV);
};
