// Copyright 2025 鸿源z。保留所有权利。


#include "Component/GenshinSdfComponent.h"
#include "ComponentUtils.h"


UGenshinSdfComponent::UGenshinSdfComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UGenshinSdfComponent::BeginPlay()
{
	Super::BeginPlay();

	
	ParentMeshComponent = Cast<USkeletalMeshComponent>(ComponentUtils::GetAttachedParent(this));
	if (ParentMeshComponent)
	{
		FaceMaterialInstance = ParentMeshComponent->CreateDynamicMaterialInstance(FaceID,nullptr,"Face");
	}
}



void UGenshinSdfComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector Forward = ParentMeshComponent->GetSocketLocation("SDF_F");
	const FVector Right = ParentMeshComponent->GetSocketLocation("SDF_R");
	const FVector Head = ParentMeshComponent->GetSocketLocation("Head");

	FaceMaterialInstance->SetVectorParameterValue("SDF_F",(Forward-Head).GetSafeNormal());
	FaceMaterialInstance->SetVectorParameterValue("SDF_R",(Right-Head).GetSafeNormal());
}

