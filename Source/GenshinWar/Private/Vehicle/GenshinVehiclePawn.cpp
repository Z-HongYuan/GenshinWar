// Copyright 2025 鸿源z。保留所有权利。


#include "Vehicle/GenshinVehiclePawn.h"

AGenshinVehiclePawn::AGenshinVehiclePawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UGenshinAttributeSet>(TEXT("AttributeSet"));

	GetMesh()->SetRenderCustomDepth(true);
	
	Tags.Add(FName("NeedCamera"));
}

void AGenshinVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	
}
