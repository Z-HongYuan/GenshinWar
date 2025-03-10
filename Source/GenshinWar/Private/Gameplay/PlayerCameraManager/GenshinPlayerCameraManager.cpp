// Copyright 2025 鸿源z。保留所有权利。


#include "Gameplay/PlayerCameraManager/GenshinPlayerCameraManager.h"

void AGenshinPlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	
	 /**
	Super::UpdateViewTargetInternal(OutVT, DeltaTime);
	 if (OutVT.Target)
	 {
	 	FVector OutLocation;
	 	FRotator OutRotation;
	 	float OutFOV;
	
	 	if (BlueprintUpdateCamera(OutVT.Target, OutLocation, OutRotation, OutFOV))
	 	{
	 		OutVT.POV.Location = OutLocation;
	 		OutVT.POV.Rotation = OutRotation;
	 		OutVT.POV.FOV = OutFOV;
	 	}
	 	else
	 	{
	 		OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
	 	}
	 }
	不调用,实现自己的逻辑
	*/
	
	if (OutVT.Target)
	{
		FVector OutLocation;
		FRotator OutRotation;
		float OutFOV;
		
		if (OutVT.Target->ActorHasTag(FName("NeedCamera")))
		{
			CalculateCameraParameters(OutVT.Target, OutLocation, OutRotation, OutFOV);
			OutVT.POV.Location = OutLocation;
			OutVT.POV.Rotation = OutRotation;
			OutVT.POV.FOV = OutFOV;
		}
		else
		{
			OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
		}
	}
	
}

void AGenshinPlayerCameraManager::CalculateCameraParameters(AActor* CameraTarget, FVector& NewCameraLocation,
	FRotator& NewCameraRotation, float& NewCameraFOV)
{
	NewCameraFOV=90;
}
