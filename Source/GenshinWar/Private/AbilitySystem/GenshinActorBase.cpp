// Copyright 2025 鸿源z。保留所有权利。


#include "AbilitySystem/GenshinActorBase.h"


AGenshinActorBase::AGenshinActorBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystem=CreateDefaultSubobject<UGenshinAbilitySystemComponent>(TEXT("AbilitySystem"));

}


void AGenshinActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystem->InitAbilityActorInfo(this,this);

}

