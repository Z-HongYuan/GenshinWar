// Copyright 2025 鸿源z。保留所有权利。

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenshinSdfComponent.generated.h"

/**
 * SDF组件,请附加在Mesh下
 * 需要骨骼拥有下列插槽
 * Head
 * SDF_F
 * SDF_R
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINWAR_API UGenshinSdfComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	UGenshinSdfComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "SDF")
	int32 FaceID;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "SDF")
	TObjectPtr<USkeletalMeshComponent> ParentMeshComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "SDF")
	TObjectPtr<UMaterialInstanceDynamic> FaceMaterialInstance;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
